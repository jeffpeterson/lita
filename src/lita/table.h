#ifndef lita_table_h
#define lita_table_h

#include "common.h"
#include "ecs.h"
#include "value.h"

typedef struct ObjIterator ObjIterator;
typedef struct Obj Obj;

typedef struct Entry {
  Value key;
  Value value;
} Entry;

typedef struct Table {
  int len;      /** Number of entries stored. */
  int total;    /** Total number of used entries, including tombstones. */
  int capacity; /** Number of entries allocated. */
  Entry *entries;
} Table;

void initTable(Table *table);
void freeTable(Table *table);

bool tableHas(Table *table, Value key);
bool tableGet(Table *table, Value key, Value *value);
/**
 * Returns whether key is new.
 */
bool tableSet(Table *table, Value key, Value value);
bool tableDelete(Table *table, Value key);
void tableMerge(Table *from, Table *to);
double tableInc(Table *table, Value key, double amt);

Obj *tableFindObj(Table *table, const char *bytes, int length, Hash hash);

ObjIterator *iterateTable(Table *table);

void tableRemoveWhite(Table *table);
void markTable(Table *table);
char *tableBytes(Table *table, int length);
int inspectTable(FILE *io, Table *table);

extern ECS_COMPONENT_DECLARE(Table);

void TablesImport(World *world);

#endif
