#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <limits.h>
#include <stdio.h>
#include "linked_list.h"

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

void print_int_arr(int *arr, int size) {
  printf("\nARRAY: \n");
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void print_linked_list(Node *head) {
  for (Node *it = head; it != NULL; it = it->next) {
    printf("%d ", it->data);
  }
  printf("\n");
}

void test_size() {
  MyLinkedList *l_list = linked_list();
  int s = 15;
  int *rand_arr = generate_int_arr(15, 1, 100);
  for (int i = 0; i < s; i++) {
    push_front(l_list, rand_arr[i]);
  }
  printf("\n[TEST_SIZE]\n %d = %d\n", size(l_list), s);
  assert(size(l_list) == s);
}

void test_push_front() {
  MyLinkedList *l_list = linked_list();
  int s = 15;
  int *rand_arr = generate_int_arr(s, 1, 50);
  for (int i = 0; i < s; i++) {
    push_front(l_list, rand_arr[i]);
  }
  int c = 0;
  printf("\n[TEST_PUSH_FRONT]\n");
  for (Node *it = head(l_list); it != NULL; it = it->next) {
    printf("%d = %d; ", it->data, rand_arr[s - c - 1]);
    assert(it->data == rand_arr[s - c - 1]);
    c += 1;
  }
  printf("\n");
}

void test_push_back() {
  MyLinkedList *l_list = linked_list();
  int s = 25;
  int *rand_arr = generate_int_arr(s, 1, 100);
  for (int i = 0; i < s; i++) {
    push_back(l_list, rand_arr[i]);
  }
  int c = 0;
  printf("\n[TEST_PUSH_BACK]\n");
  for (Node *it = head(l_list); it != NULL; it = it->next) {
    printf("%d = %d; ", it->data, rand_arr[c]);
    assert(it->data == rand_arr[c]);
    c += 1;
  }
  printf("\n");
}

void test_pop_front() {
  MyLinkedList *l_list = linked_list();
  int s = 3;
  int *rand_arr = generate_int_arr(s, 1, 100);
  for (int i = 0; i < s; i++) {
    push_back(l_list, rand_arr[i]);
  }
  int c = 0;
  printf("\n[TEST_POP_FRONT]\n");
  int popped1 = pop_front(l_list);
  int popped2 = pop_front(l_list);
  int popped3 = pop_front(l_list);
  printf("Added: %d %d %d Popped: %d %d %d\n", rand_arr[0], rand_arr[1], rand_arr[2], popped1, popped2, popped3);

  assert(popped1 = rand_arr[0]);
  assert(popped1 = rand_arr[1]);
  assert(popped1 = rand_arr[2]);
  assert(size(l_list) == 0);
}

void test_pop_back() {
  MyLinkedList *l_list = linked_list();
  int s = 3;
  int *rand_arr = generate_int_arr(s, 1, 100);
  for (int i = 0; i < s; i++) {
    push_back(l_list, rand_arr[i]);
  }
  int c = 0;
  printf("\n[TEST_POP_BACK]\n");
  int popped1 = pop_back(l_list);
  int popped2 = pop_back(l_list);
  int popped3 = pop_back(l_list);
  printf("Added: %d %d %d Popped: %d %d %d\n", rand_arr[0], rand_arr[1], rand_arr[2], popped1, popped2, popped3);

  assert(popped1 = rand_arr[2]);
  assert(popped1 = rand_arr[1]);
  assert(popped1 = rand_arr[0]);
  assert(size(l_list) == 0);
}

void test_front_back() {
  MyLinkedList *l_list = linked_list();
  int s = 100;
  int *rand_arr = generate_int_arr(s, 1, 100);
  for (int i = 0; i < s; i++) {
    push_back(l_list, rand_arr[i]);
  }
  printf("\n[TEST_FRONT_BACK]\n");
  int f_list = front(l_list);
  int b_list = back(l_list);
  printf("Front: %d == %d Back: %d == %d\n", f_list, rand_arr[0], b_list, rand_arr[s-1]);
  assert(f_list == rand_arr[0]);
  assert(b_list == rand_arr[s-1]);
}


void test_value_at() {
  MyLinkedList *l_list = linked_list();
  int s = 25;
  int *rand_arr = generate_int_arr(s, 1, 100);
  for (int i = 0; i < s; i++) {
    push_back(l_list, rand_arr[i]);
  }
  printf("\n[TEST_VALUE_AT]\n");
  for (int i = 0; i < s; i++) {
    printf("%d == %d; ", rand_arr[i], value_at(l_list, i));
    assert(rand_arr[i] == value_at(l_list, i));
  }
  printf("\n");
}

void test_insert_erase() {
  MyLinkedList *l_list = linked_list();
  int s = 5;
  int *rand_arr = generate_int_arr(s, 1, 100);
  for (int i = 0; i < s; i++) {
    push_back(l_list, rand_arr[i]);
  }
  printf("\n[TEST_INSERT_ERASE]\n");
  print_linked_list(l_list->head);
  int inserts = 3;
  int *insert_values = generate_int_arr(inserts, 1, 100);
  int *insert_indexes = generate_int_arr(inserts, 0, s - 1);
  for (int i = 0; i < inserts; i++) {
    printf("Insert %d at index %d\n", insert_values[i], insert_indexes[i]);
    insert(l_list, insert_indexes[i], insert_values[i]);
  }
  print_linked_list(l_list->head);
}

void test_value_n_from_end() {
  
}

void test_reverse() {
  MyLinkedList *l_list = linked_list();
  int s = 300;
  int *rand_arr = generate_int_arr(s, 1, 100);
  for (int i = 0; i < s; i++) {
    push_back(l_list, rand_arr[i]);
  }
  printf("\n[TEST_REVERSE]\n");
  reverse(l_list);
  for (int i = 0; i < s; i++) {
    printf("%d == %d; ", rand_arr[s - i - 1], value_at(l_list, i));
    assert(rand_arr[s - i - 1] == value_at(l_list, i));
  }
}

void test_find() {
  MyLinkedList *l_list = linked_list();
  int s = 300;
  int *rand_arr = generate_int_arr(s, 1, 100);
  for (int i = 0; i < s; i++) {
    push_back(l_list, rand_arr[i]);
  }
  printf("\n[TEST_FIND]\n");
  int tests = 50;
  int *rand_indexes = generate_int_arr(tests, 0, s - 1);
  for (int i = 0; i < tests; i++) {
    int found = find(l_list, rand_arr[rand_indexes[i]]);
    printf("Found %d at %d\n", rand_arr[rand_indexes[i]], found);
    assert((found == rand_indexes[i]) || (rand_arr[found] == rand_arr[rand_indexes[i]]));
  }
  // unfound tests
  int not_found_tests = 5;
  int *not_found = generate_int_arr(not_found_tests, 200, 300);
  for (int i = 0; i < not_found_tests; i++) {
    int found = find(l_list, not_found[i]);
    assert(found == -1);
  }
}

void run_tests(int amount) {
  for (int i = 1; i <= amount; i++) {
    test_push_front();
    test_push_back();
    test_size();
    test_pop_front();
    test_pop_back();
    test_front_back();
    test_value_at();
    test_insert_erase();
    test_reverse();
    test_find();
  }
}

int main() {
  srand((unsigned int) time(NULL));
  run_tests(50);
}