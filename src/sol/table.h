#ifndef sol_table_h
#define sol_table_h

#include "common.h"
#include "object.h"
#include "value.h"

typedef struct Entry {
  Value key;
  Value value;
} Entry;

typedef struct Table {
  int count;
  int capacity;
  Entry *entries;
} Table;

void initTable(Table *table);
void freeTable(Table *table);
bool tableGet(Table *table, Value key, Value *value);

/**
 * Returns whether key is new.
 */
bool tableSet(Table *table, Value key, Value value);
bool tableDelete(Table *table, Value key);
void tableAddAll(Table *from, Table *to);
double tableInc(Table *table, Value key, double amt);

Obj *tableFindObj(Table *table, ObjType type, const char *bytes, int length,
                  Hash hash);
void tableRemoveWhite(Table *table);
void markTable(Table *table);
void fprintTable(FILE *io, Table *table);

#endif
