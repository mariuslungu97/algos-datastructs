#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "../utils/utils.h"
#include "bst.h"

void test_bst() {
  // insert, get node count, print values, delete tree, is in tree, get min, get max, delete value
  // get successor, get predecessor 
  BST *tree = binary_search_tree();
  int insert_size = 10;
  int *insert_arr = generate_int_arr(insert_size, 1, 100);
  print_int_arr(insert_arr, insert_size, "Array to be inserted");
  for (int i = 0; i < insert_size; i++) {
    insert(tree, insert_arr[i]);
  }
  printf("Node count: %d\n", get_node_count(tree)); // 10
  print_values(tree);
  assert(is_in_tree(tree, insert_arr[0]) == 1);
  assert(is_in_tree(tree, insert_arr[3]) == 1);
  assert(is_in_tree(tree, insert_arr[5]) == 1);
  assert(is_in_tree(tree, 101) == 0);
  printf("Min: %d\n", get_min(tree));
  printf("Max: %d\n", get_max(tree));
  delete_value(tree, insert_arr[0]); // delete first from insert_arr
  delete_value(tree, insert_arr[insert_size - 1]); // delete last from insert_arr
  print_values(tree);
  printf("Successor of %d is %d", insert_arr[8], get_successor(tree, insert_arr[8]));
  printf("Predecessor of %d is %d", insert_arr[1], get_predecessor(tree, insert_arr[1]));
}

int main() {
  
  srand((unsigned int) time(NULL));
  test_bst();
  return 0;
}