#include <stdlib.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "table.h"
#include "value.h"

#define TABLE_MAX_LOAD 0.75

void initTable(Table *table) {
  // Todo: Cache the table's size without tombstones.
  table->count = 0;
  table->capacity = 0;
  table->entries = NULL;
}

void freeTable(Table *table) {
  FREE_ARRAY(Entry, table->entries, table->capacity);
  initTable(table);
}

static Entry *findEntry(Entry *entries, int capacity, Value key) {
  uint32_t index =
      hashValue(key) & (capacity - 1); // Optimized `% capacity` when 2^n

  /**
   * Track the first tombstone we find so we can insert into it.
   *
   * An empty bucket has key=VOID_VAL and value=NIL_VAL.
   * A tombstone has key=VOID_VAL and value=not-nil.
   */
  Entry *tombstone = NULL;

  for (;;) {
    Entry *entry = &entries[index];

    if (IS_VOID(entry->key)) {
      if (IS_NIL(entry->value)) {
        // Return the tombstone if we had found one so the caller
        // is able to insert into it, saving space.
        return tombstone != NULL ? tombstone : entry;
      } else {
        // Track the first tombstone we find.
        if (tombstone == NULL)
          tombstone = entry;
      }
    } else if (entry->key == key) {
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

  table->count = 0;
  for (int i = 0; i < table->capacity; i++) {
    Entry *entry = &table->entries[i];
    if (IS_VOID(entry->key))
      continue;

    Entry *dest = findEntry(entries, capacity, entry->key);
    dest->key = entry->key;
    dest->value = entry->value;
    table->count++;
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
  if (table->count == 0)
    return false;

  Entry *entry = findEntry(table->entries, table->capacity, key);
  if (IS_VOID(entry->key))
    return false;

  *value = entry->value;
  return true;
}

bool tableSet(Table *table, Value key, Value value) {
  if (table->count + 1 > table->capacity * TABLE_MAX_LOAD) {
    int capacity = GROW_CAPACITY(table->capacity);
    adjustCapacity(table, capacity);
  }

  Entry *entry = findEntry(table->entries, table->capacity, key);
  bool isNewKey = IS_VOID(entry->key);
  if (isNewKey && IS_NIL(entry->value))
    table->count++;

  entry->key = key;
  entry->value = value;
  return isNewKey;
}

double tableInc(Table *table, Value key, double amt) {
  Value count;
  if (tableGet(table, key, &count) && IS_NUMBER(count)) {
    amt += AS_NUMBER(count);
  }
  tableSet(table, key, NUMBER_VAL(amt));
  return amt;
}

bool tableDelete(Table *table, Value key) {
  if (table->count == 0)
    return false;

  // Find the entry.
  Entry *entry = findEntry(table->entries, table->capacity, key);
  if (IS_VOID(entry->key))
    return false;

  // Place a tombstone in the entry.
  entry->key = VOID_VAL;
  entry->value = BOOL_VAL(true);
  return true;
}

void tableAddAll(Table *from, Table *to) {
  for (int i = 0; i < from->capacity; i++) {
    Entry *entry = &from->entries[i];
    if (!IS_VOID(entry->key))
      tableSet(to, entry->key, entry->value);
  }
}

Obj *tableFindObj(Table *table, ObjType type, const char *bytes, int length,
                  Hash hash) {
  if (table->count == 0)
    return NULL;

  uint32_t index =
      hash & (table->capacity - 1); // Optimized `% table->capacity` when 2^n

  for (;;) {
    Entry *entry = &table->entries[index];
    if (IS_OBJ(entry->key)) {
      Obj *obj = AS_OBJ(entry->key);

      if (obj->hash == hash) {
        const char *objBytes = objectBytes(obj, length);
        if (objBytes != NULL && memcmp(bytes, objBytes, length) == 0)
          return AS_OBJ(entry->key);
      }
    } else {
      // Stop if we find an empty non-tombstone entry.
      if (IS_VOID(entry->key) && IS_NIL(entry->value))
        return NULL;

      // Otherwise, skip. Only objects are interned.
    }

    index = (index + 1) &
            (table->capacity - 1); // Optimized `% table->capacity` when 2^n
  }
}

void tableRemoveWhite(Table *table) {
  for (int i = 0; i < table->capacity; i++) {
    Entry *entry = &table->entries[i];
    if (IS_NIL(entry->key) || !IS_OBJ(entry->key))
      continue;

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

void fprintTable(FILE *io, Table *table) {
  fprintf(io, " (%d entries) {\n", table->count);
  for (int i = 0; i < table->capacity; i++) {
    Entry *entry = &table->entries[i];

    if (!IS_VOID(entry->key)) {
      fprintf(io, "  ");
      fprintValue(io, entry->key);
      fprintf(io, " => ");
      fprintValue(io, entry->value);
      fprintf(io, "\n");
    }
  }
  fprintf(io, "}");
}
