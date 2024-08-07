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
  uint32_t index =
      hash_value(key) & (capacity - 1); // Optimized `% capacity` when 2^n

  /**
   * Track the first tombstone we find so we can insert into it.
   *
   * An empty bucket has key=VOID_VAL and value=NIL_VAL.
   * A tombstone has key=VOID_VAL and value=not-nil.
   */
  Entry *tombstone = NULL;

  for (;;) {
    Entry *entry = &entries[index];

    if (is_void(entry->key)) {
      if (is_nil(entry->value)) {
        // Return the tombstone if we had found one so the caller
        // is able to insert into it, saving space.
        return tombstone != NULL ? tombstone : entry;
      } else {
        // Track the first tombstone we find.
        if (tombstone == NULL) tombstone = entry;
      }
    } else if (valuesEqual(entry->key, key)) {
      // We found an entry, return it.
      return entry;
    }

    index = (index + 1) & (capacity - 1); // Optimized `% capacity` when 2^n
  }
}

static void adjustCapacity(Table *table, int capacity) {
  Entry *entries = ALLOCATE(Entry, capacity);
  for (int i = 0; i < capacity; i++) {
    entries[i].key = VOID_VAL;
    entries[i].value = NIL_VAL;
  }

  table->total = 0;
  for (int i = 0; i < table->capacity; i++) {
    Entry *entry = &table->entries[i];
    if (is_void(entry->key)) continue;

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
  if (is_void(entry->key)) return false;

  *value = entry->value;
  return true;
}

bool tableSet(Table *table, Value key, Value value) {
  if (table->total + 1 > table->capacity * TABLE_MAX_LOAD) {
    int capacity = GROW_CAPACITY(table->capacity);
    adjustCapacity(table, capacity);
  }

  Entry *entry = findEntry(table->entries, table->capacity, key);
  bool isNewKey = is_void(entry->key);
  if (isNewKey && is_nil(entry->value)) table->total++, table->len++;

  entry->key = key;
  entry->value = value;
  return isNewKey;
}

/** Increment the value at `key` by `amt`. */
double tableInc(Table *table, Value key, double amt) {
  Value count;
  if (tableGet(table, key, &count) && is_num(count)) {
    amt += AS_NUMBER(count);
  }
  tableSet(table, key, NUMBER_VAL(amt));
  return amt;
}

bool tableDelete(Table *table, Value key) {
  if (table->len == 0) return false;

  // Find the entry.
  Entry *entry = findEntry(table->entries, table->capacity, key);
  if (is_void(entry->key)) return false;

  // Place a tombstone in the entry.
  entry->key = VOID_VAL;
  entry->value = BOOL_VAL(true);
  table->len--;
  return true;
}

void tableMerge(Table *from, Table *to) {
  for (int i = 0; i < from->capacity; i++) {
    Entry *entry = &from->entries[i];
    if (!is_void(entry->key)) tableSet(to, entry->key, entry->value);
  }
}

static void iterate_table_entries_next(ObjIterator *iter) {
  Entry *entry = (Entry *)iter->current;
  iter->current = (Value *)++entry;
}

/** Iterates over all entries of this table. */
static ObjIterator *iterate_table_entries(Table *table) {
  ObjIterator *iter = new_iterator();

  iter->size = 2;
  iter->total = table->capacity;
  iter->current = (Value *)table->entries;
  iter->next = iterate_table_entries_next;
  iter->done = table->capacity == 0;

  return iter;
}

static void iterate_table_next(ObjIterator *iter) {
  Entry *entry = (Entry *)iter->current;
  ObjIterator *entries = as_iterator(iter->state);

  while (iterate_next(entries))
    if (is_void(entry->key)) continue;
    else {
      iter->current = (Value *)entry;
      return;
    }

  iter->done = true;
}

/** Iterates over the key-value pairs of this table. */
ObjIterator *iterate_table(Table *table) {
  ObjIterator *entries = iterate_table_entries(table);
  ObjIterator *iter = new_iterator();

  iter->state = OBJ_VAL(entries);
  iter->size = 2;
  iter->total = table->len;
  iter->current = (Value *)table->entries;
  iter->next = iterate_table_next;
  iter->done = table->len == 0;

  return iter;
}

Obj *tableFindObj(Table *table, ObjType type, const char *bytes, int length,
                  Hash hash) {
  if (table->total == 0) return NULL;

  uint32_t index =
      hash & (table->capacity - 1); // Optimized `% table->capacity` when 2^n

  for (;;) {
    Entry *entry = &table->entries[index];
    if (is_obj(entry->key)) {
      Obj *obj = AS_OBJ(entry->key);

      if (obj->hash == hash) {
        const char *objBytes = objectBytes(obj, length);
        if (objBytes != NULL && memcmp(bytes, objBytes, length) == 0)
          return AS_OBJ(entry->key);
      }
    } else {
      // Stop if we find an empty non-tombstone entry.
      if (is_void(entry->key) && is_nil(entry->value)) return NULL;

      // Otherwise, skip. Only objects are interned.
    }

    index = (index + 1) &
            (table->capacity - 1); // Optimized `% table->capacity` when 2^n
  }
}

void tableRemoveWhite(Table *table) {
  for (int i = 0; i < table->capacity; i++) {
    Entry *entry = &table->entries[i];
    if (is_nil(entry->key) || !is_obj(entry->key)) continue;

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

char *table_bytes(Table *table, int length) {
  if (length != table->len * sizeof(Entry)) return NULL;
  return (char *)table->entries;
}

int inspect_table(FILE *io, Table *table) {
  int out = 0;
  int idx = 0;
  for (int i = 0; i < table->capacity; i++) {
    Entry *entry = &table->entries[i];

    if (is_void(entry->key)) continue;

    if (is_string(entry->key)) {
      out += (idx > 0 ? fputs(", ", io) : 0) +
             fprintf(io, FG_GREEN "%s" FG_DEFAULT ": ",
                     AS_STRING(entry->key)->chars) +
             inspect_value(io, entry->value);
    } else {
      out += fprintf(io, " ") + inspect_value(io, entry->key) +
             fprintf(io, " => ") + inspect_value(io, entry->value);
    }
    idx++;
  }

  return out;
}

int fprintTableVerbose(FILE *io, Table *table) {
  int out = fprintf(io, " (%d entries) {\n", table->len);
  for (int i = 0; i < table->capacity; i++) {
    Entry *entry = &table->entries[i];

    if (!is_void(entry->key)) {
      out += fprintf(io, "  ") + inspect_value(io, entry->key) +
             fprintf(io, " => ") + inspect_value(io, entry->value) +
             fprintf(io, "\n");
    }
  }
  return fprintf(io, "}") + out;
}
