#include <assert.h>

#include <stdlib.h>
#include <string.h>

#include "iterator.h"
#include "memory.h"
#include "object.h"
#include "string.h"
#include "table.h"
#include "term.h"

#define TABLE_MAX_LOAD 0.75

void initTable(Table *table) {
  table->len = 0;
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

  table->total = 0;
  for (int i = 0; i < table->capacity; i++) {
    Entry *entry = &table->entries[i];
    if (isVoid(entry->key)) continue;

    Entry *dest = findEntry(entries, capacity, entry->key);
    dest->key = entry->key;
    dest->value = entry->value;
    table->total++;
  }

  FREE_ARRAY(Entry, table->entries, table->capacity);
  table->entries = entries;
  table->capacity = capacity;
}

bool tableHas(Table *table, Value key) {
  Value v;
  return tableGet(table, key, &v);
}

bool tableGet(Table *table, Value key, Value *value) {
  if (table->len == 0) return false;

  Entry *entry = findEntry(table->entries, table->capacity, key);
  if (isVoid(entry->key)) return false;

  if (value) *value = entry->value;
  return true;
}

bool tableSet(Table *table, Value key, Value value) {
  if (table->total + 1 > table->capacity * TABLE_MAX_LOAD) {
    int capacity = GROW_CAPACITY(table->capacity);
    adjustCapacity(table, capacity);
  }

  Entry *entry = findEntry(table->entries, table->capacity, key);
  bool isNewKey = isVoid(entry->key);
  if (isNewKey && isNil(entry->value)) table->total++, table->len++;

  entry->key = key;
  entry->value = value;
  return isNewKey;
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
  if (table->len == 0) return false;

  // Find the entry.
  Entry *entry = findEntry(table->entries, table->capacity, key);
  if (isVoid(entry->key)) return false;

  // Place a tombstone in the entry.
  entry->key = VOID_VAL;
  entry->value = BOOL_VAL(true);
  table->len--;
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
  iter->total = table->capacity;
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
  iter->total = table->len;
  iter->current = (Value *)table->entries;
  iter->next = iterateTableNext;
  iter->done = table->len == 0;

  return iter;
}

Obj *tableFindObj(Table *table, Hash hash) {
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

void tableRemoveWhite(Table *table) {
  for (int i = 0; i < table->capacity; i++) {
    Entry *entry = &table->entries[i];
    if (isNil(entry->key) || !isObject(entry->key)) continue;

    if (!AS_OBJ(entry->key)->isMarked) {
      tableDelete(table, entry->key);
    }
  }
}

void markTable(Table *table) {
  for (int i = 0; i < table->capacity; i++) {
    Entry *entry = &table->entries[i];
    markValue(entry->key);
    markValue(entry->value);
  }
}

int inspectTable(FILE *io, Table *table) {
  int out = 0;
  int idx = 0;
  for (int i = 0; i < table->capacity; i++) {
    Entry *entry = &table->entries[i];

    if (isVoid(entry->key)) continue;

    if (isString(entry->key)) {
      out += (idx > 0 ? fputs(", ", io) : 0) +
             fprintf(io, FG_GREEN "%s" FG_DEFAULT ": ",
                     asString(entry->key)->chars) +
             inspectValue(io, entry->value);
    } else {
      out += fprintf(io, " ") + inspectValue(io, entry->key) +
             fprintf(io, " => ") + inspectValue(io, entry->value);
    }
    idx++;
  }

  return out;
}

int fprintTableVerbose(FILE *io, Table *table) {
  int out = fprintf(io, " (%d entries) {\n", table->len);
  for (int i = 0; i < table->capacity; i++) {
    Entry *entry = &table->entries[i];

    if (!isVoid(entry->key)) {
      out += fprintf(io, "  ") + inspectValue(io, entry->key) +
             fprintf(io, " => ") + inspectValue(io, entry->value) +
             fprintf(io, "\n");
    }
  }
  return fprintf(io, "}") + out;
}

void hashTable(HashState *state, Table *table) {
  updateHash(state, &table->entries, sizeof(Entry) * table->capacity);
}

ECS_COMPONENT_DECLARE(Table);

void TablesImport(World *world) {
  ECS_MODULE(world, Tables);
  ECS_COMPONENT_DEFINE(world, Table);
}
