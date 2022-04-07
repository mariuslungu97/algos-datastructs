/*
  Hash Table Implementation using Linear Probing
  Performance for insertion, deletion, search: O(1)
  Double capacity when load factor crosses threshold

  Considerations / Requirements:

  how do I express a flagged element?
  hash map must be able to support string and int based keys
  do I need to work with arrays of pointers (pointer to pointer)?
*/

#ifndef HASH_TABLE_H

#include <limits.h>

#define HASH_TABLE_H
#define ARRAY_ENTRY_FLAG_DELETED INT_MIN
#define DEFAULT_MIN_LOAD_FACTOR 0.10
#define DEFAULT_MAX_LOAD_FACTOR 0.65
#define DEFAULT_TABLE_CAPACITY 17
#define PRIME_FOR_HASH 11

typedef struct ArrayEntry
{
  int key;
  int value;
} ArrayEntry;

typedef struct LinkedEntry
{
  int key;
  int value;
  struct LinkedEntry *next;
} LinkedEntry;

typedef struct HashTableWithChaining
{
  int size;
  int capacity;
  LinkedEntry **data;
} HashTableWithChaining;

typedef struct OpenHashTable
{
  int size;
  int capacity;
  ArrayEntry **data;
} OpenHashTable;

// helpers
static int is_prime(unsigned int nr);
static unsigned int next_prime(unsigned int nr);

// hash functions
static int hash_int(int nr, int m);
static int hash_double_int(int nr, int m, int i);

// internal structs' constructors
static ArrayEntry *array_entry(int key, int value);
static LinkedEntry *linked_entry(int key, int value, LinkedEntry *next);
static void flag_delete_array_entry(ArrayEntry *entry);
static int is_array_entry_flag_deleted(ArrayEntry *entry);

// open structs' constructors
HashTableWithChaining *hash_table_with_chaining();
OpenHashTable *open_hash_table();

// internal structs' methods
static void add_linked_entry(LinkedEntry **root, LinkedEntry *entry);

// internal hash table methods
static void resize_chained_hash_table(HashTableWithChaining *h_table, int new_capacity);
static void resize_open_hash_table(OpenHashTable *h_table, int new_capacity);

// open hash table methods
void add_chained_entry(HashTableWithChaining *h_table, int key, int value);
int exists_chained_entry(HashTableWithChaining *h_table, int key);
int get_chained_entry(HashTableWithChaining *h_table, int key);
void remove_chained_entry(HashTableWithChaining *h_table, int key);

void add_open_entry(OpenHashTable *h_table, int key, int value);
int exists_open_entry(OpenHashTable *h_table, int key);
int get_open_entry(OpenHashTable *h_table, int key);
void remove_open_entry(OpenHashTable *h_table, int key);

#endif
