#ifndef lita_store_h
#define lita_store_h

// #include <db.h>
// #include <ossp/uuid.h>
#include <string.h>

#include "common.h"

typedef enum StoreEntryType {
  ENTRY_BYTES,
  ENTRY_IDS,
} StoreEntryType;

typedef struct StoreEntry {
  u128 key;
  u32 len;
  u8 *bytes;
} StoreEntry;

typedef struct Store {
  u32 len;      /** Number of entries stored. */
  u32 total;    /** Total number of used entries, including tombstones. */
  u32 capacity; /** Number of entries allocated. */
  StoreEntry *entries;
} Store;

void createStore();

#endif
