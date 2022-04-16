#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heaps.h"
#include "../utils/utils.h"

void test_heap() {
  // insert, extract max, remove_at
  int insert_arr[6] = {32, 12, 49, 44, 88, 20};
  Heap *h = heap(10);
  insert(h, insert_arr[0]); // 32
  insert(h, insert_arr[2]); // 49
  insert(h, insert_arr[3]); // 44
  printf("Max: %d\n", extract_max(h)); // 49
  remove_at(h, 1); // 32
  printf("Max: %d\n", extract_max(h)); // 44
  printf("Is empty? %d\n", is_empty(h)); // 1 (true)
}

void test_heap_sort() {
  int size = 50;
  int *arr = generate_int_arr(size, 1, 100);
  print_int_arr(arr, size, "Unsorted Array:");
  heap_sort(arr, size);
  print_int_arr(arr, size, "Sorted Array:");
}

int main() {
  srand((unsigned int) time(NULL));
  // test_heap_sort();
  test_heap();
}