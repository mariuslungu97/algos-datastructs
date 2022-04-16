#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <execinfo.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

// function used to print stacktrace (debugging purposes)
void handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

void print_int_arr(int *arr, int size, char *name) {
  printf("\nARRAY %s:\n", name);
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

// generate int in [min, max] range
int generate_int(int min, int max) {
  if (min > max) return INT_MAX;
  int r = rand() % (max + 1 - min) + min;
  return r;
}

int *generate_int_arr(int size, int min_int, int max_int) {
  if (size <= 0) {
    return NULL;
  }
  int *new_arr = malloc(size * sizeof(int));
  if (new_arr == NULL) {
    return NULL;
  }
  for (int i = 0; i < size; i++) {
    new_arr[i] = generate_int(min_int, max_int);
  }
  return new_arr;
}

void test_memset_fc() {
  int cap = 1000;
  int **ptr_arr = malloc(cap * sizeof(*ptr_arr));
  if (ptr_arr == NULL)
    return;
  memset(ptr_arr, NULL, cap);
  for (int i = 0; i < cap; i++) {
    printf("p = %p\n", *(ptr_arr + i));
  }
}

void test_exists_open_entry() {
  OpenHashTable *open_h_table = open_hash_table();
  int to_add = 8;
  int *keys = generate_int_arr(to_add, 1, 50);
  int *values = generate_int_arr(to_add, 100, 1000);
  print_int_arr(keys, to_add, "[KEYS]");
  print_int_arr(values, to_add, "[VALUES]");

  for (int i = 0; i < to_add; i++) {
    // add_chained_entry(chained_h_table, keys[i], values[i]);
    add_open_entry(open_h_table, keys[i], values[i]);
  }

  for (int i = 0; i < to_add; i++) {
    int key_exists = exists_open_entry(open_h_table, keys[i]);
    printf("Does key = %d exist? %d\n", keys[i], key_exists);
  }
}

/* General Tests */
void test_hash_table() {
  
  OpenHashTable *open_h_table = open_hash_table();
  HashTableWithChaining *chained_h_table = hash_table_with_chaining();

  int to_add = 1000;
  int *keys = generate_int_arr(to_add, 1, 1000);
  int *values = generate_int_arr(to_add, 1, 10000);
  print_int_arr(keys, to_add, "[KEYS]");
  print_int_arr(values, to_add, "[VALUES]");

  for (int i = 0; i < to_add; i++) {
    add_chained_entry(chained_h_table, keys[i], values[i]);
    add_open_entry(open_h_table, keys[i], values[i]);
  }

  for (int i = 0; i < to_add; i++) {
    printf("[Hash Table With Chaining] Value %d at key %d\n", get_chained_entry(chained_h_table, keys[i]), keys[i]);
    printf("[Open-Addressing Hash Table] Value %d at key %d\n", get_open_entry(open_h_table, keys[i]), keys[i]);
  }

  printf("[Hash Table With Chaining] Capacity = %d\n ; Size = %d\n", chained_h_table->capacity, chained_h_table->size);
  printf("[Open-Addressing Hash Table] Capacity = %d\n ; Size = %d\n", open_h_table->capacity, open_h_table->size);

  int to_delete = 100;
  for (int i = 0; i < to_delete; i++) {
    int delete_key = generate_int(0, to_add - 1);
    if (exists_chained_entry(chained_h_table, keys[delete_key])) {
      printf("Delete key = %d from Hash Table with chaining ...\n", keys[delete_key]);
      remove_chained_entry(chained_h_table, keys[delete_key]);
      assert(exists_chained_entry(chained_h_table, keys[delete_key]) == 0);
    }
    if (exists_open_entry(open_h_table, keys[delete_key])) {
      printf("Delete key = %d from Open Table ...\n", keys[delete_key]);
      remove_open_entry(open_h_table, keys[delete_key]);
      assert(exists_open_entry(open_h_table, keys[delete_key]) == 0);
    }
  }
}

void run_tests(int times) {
  if (times < 1) 
    return;
  for (int i = 0; i < times; i++) {
    // test_memset_fc();
    test_hash_table();
    // test_exists_open_entry();
  }
}

int main() {
  signal(SIGBUS, handler); // attach handler to bus errors
  signal(SIGSEGV, handler); // attach handler to segmentation errors

  srand((unsigned int) time(NULL));
  run_tests(1);

  return 0;
}