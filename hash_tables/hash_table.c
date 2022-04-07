#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_prime(unsigned int nr) {
  for (int i = 3; 1; i += 2) {
    int q = nr / i;
    if (q < i)
      return 1;
    if (nr == q * i)
      return 0;
  }
  return 1;
}

static unsigned int next_prime(unsigned int nr) {
  if (nr <= 2)
    return 2;
  if (!(nr & 1))
    ++nr;
  for (; !is_prime(nr); nr += 2)
      ;
  return nr;
}

static int hash_int(int nr, int m) {
  return (nr % m);
}

static int hash_prime(int nr) {
  return (PRIME_FOR_HASH - (nr % PRIME_FOR_HASH));
}

static int hash_double_int(int nr, int m, int i) {
  return (hash_int(nr, m) + i * hash_prime(nr)) % m;
}

static ArrayEntry *array_entry(int key, int value) {
  ArrayEntry *new_entry = malloc(sizeof(*new_entry));
  if (new_entry == NULL) {
    printf("ERROR! [ARRAY_ENTRY] Struct memory cannot be allocated ... returning NULL");
    return NULL;
  }
  new_entry->key = key;
  new_entry->value = value;
  return new_entry;
}

static LinkedEntry *linked_entry(int key, int value, LinkedEntry *next) {
  LinkedEntry *new_entry = malloc(sizeof(*new_entry));
  if (new_entry == NULL) {
    printf("ERROR! [Linked_Entry] Struct memory cannot be allocated ... returning NULL");
    return NULL;
  }
  new_entry->key = key;
  new_entry->value = value;
  new_entry->next = next;
  return new_entry;
}

static void flag_delete_array_entry(ArrayEntry *entry) {

  entry->key = ARRAY_ENTRY_FLAG_DELETED;
  entry->value = ARRAY_ENTRY_FLAG_DELETED;
}

static int is_array_entry_flag_deleted(ArrayEntry *entry) {

  if (entry->key == ARRAY_ENTRY_FLAG_DELETED && entry->value == ARRAY_ENTRY_FLAG_DELETED)
    return 1;

  return 0;
}

HashTableWithChaining *hash_table_with_chaining() {
  HashTableWithChaining *h_table = malloc(sizeof(*h_table));
  if (h_table == NULL) {
    printf("ERROR! [HASH_TABLE_WITH_CHAINING] Struct memory cannot be allocated ... returning NULL");
    return NULL;
  }
  h_table->size = 0;
  h_table->capacity = DEFAULT_TABLE_CAPACITY;
  h_table->data = malloc(h_table->capacity * sizeof(*h_table->data));
  if (h_table->data == NULL) {
    printf("ERROR! [HASH_TABLE_WITH_CHAINING] Data memory cannot be allocated ... returning NULL");
    free(h_table);
    return NULL;
  }
  for (int i = 0; i < h_table->capacity; i++) {
    *(h_table->data + i) = NULL;
  }
  return h_table;
}

OpenHashTable *open_hash_table() {

  OpenHashTable *h_table = malloc(sizeof(*h_table));
  if (h_table == NULL) {
    printf("ERROR! [HASH_TABLE_WITH_CHAINING] Struct memory cannot be allocated ... returning NULL");
    return NULL;
  }
  h_table->size = 0;
  h_table->capacity = DEFAULT_TABLE_CAPACITY;
  h_table->data = malloc(h_table->capacity * sizeof(*h_table->data));
  if (h_table->data == NULL) {
    printf("ERROR! [HASH_TABLE_WITH_CHAINING] Data memory cannot be allocated ... returning NULL");
    free(h_table);
    return NULL;
  }
  for (int i = 0; i < h_table->capacity; i++) {
    *(h_table->data + i) = NULL;
  }
  return h_table;
}

static void add_linked_entry(LinkedEntry **root, LinkedEntry *entry) {
  if (*root == NULL) {
    *root = entry;
    return;
  }
  LinkedEntry *tail = *root;
  while (tail->next != NULL)
    tail = tail->next;
  // reached the end of the linked chain, we can add now
  tail->next = entry;
}

static void resize_chained_hash_table(HashTableWithChaining *h_table, int new_capacity) {
  if (new_capacity < 1)
    return;
  // round capacity to its nearest, greater prime
  new_capacity = next_prime(new_capacity);
  // create new array of pointers
  size_t data_size = new_capacity * sizeof(*h_table->data);
  LinkedEntry **data = malloc(data_size);
  if (data == NULL) {
    printf("ERROR! [RESIZE_CHAINED_HASH_TABLE] Data memory cannot be allocated ... exit function!");
    return;
  }
  // start by setting all new pointers to NULL
  memset(data, NULL, data_size);
  // re-compute hashes based on new capacity 
  for (int i = 0; i < h_table->capacity; i++) {
    LinkedEntry *chain_entry = *(h_table->data + i);
    if (chain_entry == NULL)
      continue;
    
    while (chain_entry != NULL) {
      LinkedEntry *next_entry = chain_entry->next;
      chain_entry->next = NULL;
      int new_hash = hash_int(chain_entry->key, new_capacity);
      add_linked_entry((data + new_hash), chain_entry);
      chain_entry = next_entry;
    }
    // set to NULL to free later
    *(h_table->data + i) = NULL;
  }
  free(h_table->data);
  h_table->data = data;
  h_table->capacity = new_capacity;
}

static void resize_open_hash_table(OpenHashTable *h_table, int new_capacity) {

  if (new_capacity < 1)
    return;
  // round capacity to its nearest, greater prime
  new_capacity = next_prime(new_capacity);
  // create new array of pointers
  size_t data_size = new_capacity * sizeof(*h_table->data);
  ArrayEntry **data = malloc(data_size);
  if (data == NULL) {
    printf("ERROR! [RESIZE_CHAINED_HASH_TABLE] Data memory cannot be allocated ... exit function!");
    return;
  }
  // start by setting all new pointers to NULL
  memset(data, NULL, data_size);
  for (int i = 0; i < h_table->capacity; i++) {
    ArrayEntry *entry = *(h_table->data + i);
    if (entry == NULL)
      continue;
    
    if (is_array_entry_flag_deleted(entry)) {
      free(entry);
      continue;
    }

    int j = 0;
    while (*(data + hash_double_int(entry->key, new_capacity, j)) != NULL) {
      j++;
    }
    *(data + hash_double_int(entry->key, new_capacity, j)) = entry;
    *(h_table->data + i) = NULL;
  }
  free(h_table->data);
  h_table->data = data;
  h_table->capacity = new_capacity;
}

void add_chained_entry(HashTableWithChaining *h_table, int key, int value) {
  if (exists_chained_entry(h_table, key)) {
    printf("[ADD_CHAINED_ENTRY] Key = %d is already present in the hash table ... returning!\n", key);
    return;
  }
  LinkedEntry *new_entry = linked_entry(key, value, NULL);
  if (new_entry == NULL) {
    printf("ERROR! [ADD_CHAINED_ENTRY] Struct memory cannot be allocated ... returning!");
    return;
  }

  if (((float) (h_table->size + 1) / (float) h_table->capacity) > (float) DEFAULT_MAX_LOAD_FACTOR) {
    resize_chained_hash_table(h_table, h_table->capacity * 2);
  }

  int hash_index = hash_int(key, h_table->capacity);
  add_linked_entry((h_table->data + hash_index), new_entry);
  h_table->size += 1;
}

int exists_chained_entry(HashTableWithChaining *h_table, int key) {
  int hash_index = hash_int(key, h_table->capacity);
  LinkedEntry *chain_entry = *(h_table->data + hash_index);
 
  while (chain_entry != NULL) {
    if (chain_entry->key == key)
      return 1;

    chain_entry = chain_entry->next;
  }
  return 0;
}

int get_chained_entry(HashTableWithChaining *h_table, int key) {
  int hash_index = hash_int(key, h_table->capacity);
  LinkedEntry *chain_entry = *(h_table->data + hash_index);
  while (chain_entry != NULL) {
    if (chain_entry->key == key)
      return chain_entry->value;

    chain_entry = chain_entry->next;
  }

  return INT_MAX;
}

void remove_chained_entry(HashTableWithChaining *h_table, int key) {
  int removed = 0;
  int hash_index = hash_int(key, h_table->capacity);
  LinkedEntry *chain_entry = *(h_table->data + hash_index);
  LinkedEntry *prev = NULL;

  if (chain_entry != NULL && chain_entry->key == key) {
    *(h_table->data + hash_index) = chain_entry->next;
    free(chain_entry);
    removed = 1;
  }
  else {
    while (chain_entry != NULL && chain_entry->key != key) {
      prev = chain_entry;
      chain_entry = chain_entry ->next;
    }
    
    if (chain_entry != NULL) {
      prev->next = chain_entry->next;
      free(chain_entry);
      removed = 1;
    }
  }

  if (removed) {
    if ((float) (h_table->size - 1) / (float) h_table->capacity <= DEFAULT_MIN_LOAD_FACTOR)
      resize_chained_hash_table(h_table, h_table->capacity / 2);
    h_table->size -= 1;
  }
}

void add_open_entry(OpenHashTable *h_table, int key, int value) {

  if (exists_open_entry(h_table, key)) {
    printf("[ADD_OPEN_ENTRY] Key = %d is already present in the hash table ... returning!\n", key);
    return;
  }

  ArrayEntry *entry = array_entry(key, value);
  if (entry == NULL)
    return;

  if (((float) (h_table->size + 1) / (float) h_table->capacity) > DEFAULT_MAX_LOAD_FACTOR) {
    resize_open_hash_table(h_table, h_table->capacity * 2);
  }
  int i = 0;
  while (*(h_table->data + hash_double_int(key, h_table->capacity, i)) != NULL)
    i++;

  *(h_table->data + hash_double_int(key, h_table->capacity, i)) = entry;
  h_table->size += 1;
}

int exists_open_entry(OpenHashTable *h_table, int key) {

  int i = 0;
  
  while (*(h_table->data + hash_double_int(key, h_table->capacity, i)) != NULL) {
    ArrayEntry *entry = *(h_table->data + hash_double_int(key, h_table->capacity, i));

    if (!is_array_entry_flag_deleted(entry) && entry->key == key)
      return 1;
    i++;
  }
  return 0;
}

int get_open_entry(OpenHashTable *h_table, int key) {

  int i = 0;
  while (*(h_table->data + hash_double_int(key, h_table->capacity, i)) != NULL) {
    ArrayEntry *entry = *(h_table->data + hash_double_int(key, h_table->capacity, i));
    if (!is_array_entry_flag_deleted(entry) && entry->key == key)
      return entry->value;
    i++;
  }
  return INT_MAX;
}

void remove_open_entry(OpenHashTable *h_table, int key) {

  int i = 0;
  while (*(h_table->data + hash_double_int(key, h_table->capacity, i)) != NULL) {
    ArrayEntry *entry = *(h_table->data + hash_double_int(key, h_table->capacity, i));
    if (!is_array_entry_flag_deleted(entry) && entry->key == key) {
      flag_delete_array_entry(entry);
      if ((float) (h_table->size - 1) / (float) h_table->capacity <= DEFAULT_MIN_LOAD_FACTOR && next_prime(h_table->capacity / 2) >= DEFAULT_TABLE_CAPACITY)
        resize_open_hash_table(h_table, h_table->capacity / 2);
      h_table->size -= 1;
      return;
    }
    i++;
  }
}

