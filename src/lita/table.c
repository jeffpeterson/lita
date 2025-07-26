#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "iterator.h"
#include "memory.h"
#include "object.h"
#include "string.h"
#include "table.h"

#define TABLE_MAX_LOAD 0.75

void initTable(Table *table) {
  table->length = 0;
  table->total = 0;
  table->capacity = 0;
  table->entries = NULL;
}

void freeTable(Table *table) {
  FREE_ARRAY(Entry, table->entries, table->capacity);
  initTable(table);
}

static Entry *findEntry(Entry *entries, int capacity, Value key) {
  u32 index =
      valueHash(key) & (capacity - 1); // Optimized `% capacity` when 2^n

  /**
   * Track the first tombstone we find so we can insert into it.
   *
   * An empty bucket has key=VOID_VAL and value=NIL_VAL.
   * A tombstone has key=VOID_VAL and value=not-nil.
   */
  Entry *tombstone = NULL;

  for (;;) {
    Entry *entry = &entries[index];

    if (isVoid(entry->key)) {
      if (isNil(entry->value)) {
        // Return the tombstone if we had found one so the caller
        // is able to insert into it, saving space.
        return tombstone ? tombstone : entry;
      } else {
        // Track the first tombstone we find.
        if (!tombstone) tombstone = entry;
      }
    } else if (valuesEqual(entry->key, key)) {
      // We found an entry, return it.
      return entry;
    }

    index = (index + 1) & (capacity - 1); // Optimized `% capacity` when 2^n
  }
}

static void adjustCapacity(Table *table, int capacity) {
  assert(0 == (capacity & (capacity - 1))); // must be 2^n
  Entry *entries = ALLOCATE(Entry, capacity);
  for (int i = 0; i < capacity; i++) {
    entries[i].key = VOID_VAL;
    entries[i].value = NIL_VAL;
  }

  for (int i = 0; i < table->capacity; i++) {
    Entry *entry = &table->entries[i];
    if (isVoid(entry->key)) continue;

    Entry *dest = findEntry(entries, capacity, entry->key);
    dest->key = entry->key;
    dest->value = entry->value;
  }

  FREE_ARRAY(Entry, table->entries, table->capacity);
  table->entries = entries;
  table->capacity = capacity;
  table->total = table->length;
}

bool tableHas(Table *table, Value key) {
  Value v;
  return tableGet(table, key, &v);
}

bool tableGet(Table *table, Value key, Value *value) {
  if (table->length == 0) return false;

  Entry *entry = findEntry(table->entries, table->capacity, key);
  if (isVoid(entry->key)) return false;

  if (value) *value = entry->value;
  return true;
}

bool tableSet(Table *table, Value key, Value value) {
  // We use ->total to also consider tombstones. Tombstones cause slowdown and
  // adjustCapacity() removes them.
  int capacity = table->capacity;
  if (table->total + 1 > capacity * TABLE_MAX_LOAD) {
    if (table->length + 1 > capacity * TABLE_MAX_LOAD)
      capacity = GROW_CAPACITY(capacity);
    adjustCapacity(table, capacity);
  }

  Entry *entry = findEntry(table->entries, table->capacity, key);
  bool is_new_key = isVoid(entry->key);
  if (is_new_key) {
    table->length++;
    if (isNil(entry->value)) table->total++;
  }

  entry->key = key;
  entry->value = value;
  return is_new_key;
}

/** Increment the value at `key` by `amt`. */
double tableInc(Table *table, Value key, double amt) {
  Value count;
  if (tableGet(table, key, &count) && isNumber(count)) {
    amt += AS_NUMBER(count);
  }
  tableSet(table, key, NUMBER_VAL(amt));
  return amt;
}

bool tableDelete(Table *table, Value key) {
  if (table->length == 0) return false;

  // Find the entry.
  Entry *entry = findEntry(table->entries, table->capacity, key);
  if (isVoid(entry->key)) return false;

  // Place a tombstone in the entry.
  entry->key = VOID_VAL;
  entry->value = BOOL_VAL(true);
  table->length--;
  return true;
}

void tableMerge(Table *from, Table *to) {
  for (int i = 0; i < from->capacity; i++) {
    Entry *entry = &from->entries[i];
    if (!isVoid(entry->key)) tableSet(to, entry->key, entry->value);
  }
}

static void iterateTableEntriesNext(ObjIterator *iter) {
  Entry *entry = (Entry *)iter->current;
  iter->current = (Value *)++entry;
}

/** Iterates over all entries of this table. */
static ObjIterator *iterateTableEntries(Table *table) {
  ObjIterator *iter = allocateIterator();

  iter->size = 2;
  iter->length = table->capacity;
  iter->current = (Value *)table->entries;
  iter->next = iterateTableEntriesNext;
  iter->done = table->capacity == 0;

  return iter;
}

static void iterateTableNext(ObjIterator *iter) {
  Entry *entry = (Entry *)iter->current;
  ObjIterator *entries = asIterator(iter->state);

  while (iterateNext(entries))
    if (isVoid(entry->key)) continue;
    else {
      iter->current = (Value *)entry;
      return;
    }

  iter->done = true;
}

/** Iterates over the key-value pairs of this table. */
ObjIterator *iterateTable(Table *table) {
  ObjIterator *entries = iterateTableEntries(table);
  ObjIterator *iter = allocateIterator();

  iter->state = OBJ_VAL(entries);
  iter->size = 2;
  iter->length = table->length;
  iter->current = (Value *)table->entries;
  iter->next = iterateTableNext;
  iter->done = table->length == 0;

  return iter;
}

Obj *table_find_hash(Table *table, Hash hash) {
  if (table->total == 0) return NULL;

  u32 index =
      hash & (table->capacity - 1); // Optimized `% table->capacity` when 2^n

  for (;;) {
    Entry *entry = &table->entries[index];
    if (isObject(entry->key)) {
      Obj *obj = AS_OBJ(entry->key);

      if (obj->hash == hash) return AS_OBJ(entry->key);
    } else {
      // Stop if we find an empty non-tombstone entry.
      if (isVoid(entry->key) && isNil(entry->value)) return NULL;

      // Otherwise, skip. Only objects are interned.
    }

    index = (index + 1) &
            (table->capacity - 1); // Optimized `% table->capacity` when 2^n
  }
}

void markTable(Table *table) {
  for (int i = 0; i < table->capacity; i++) {
    Entry *entry = &table->entries[i];
    markValue(entry->key);
    markValue(entry->value);
  }
}

int inspectTable(FILE *io, Table *table, int depth) {
  int out = 0, idx = 0;
  int max_key = 0;

  if (!depth) out += fprintf(io, "(%d values)\n\t", table->length);

  for (int i = 0; i < table->capacity; i++) {
    Entry *entry = &table->entries[i];

    if (isVoid(entry->key)) continue;

    if (idx > 0) out += fprintf(io, ",%s", depth ? " " : "\n\t");

    out += fpad(io, &max_key, inspectValue(io, entry->key, depth + 2)) +
           fprintf(io, " => ") + inspectValue(io, entry->value, depth + 1);
    idx++;
  }

  return out;
}

void hashTable(HashState *state, Table *table) {
  updateHash(state, &table->entries, sizeof(Entry) * table->capacity);
}
