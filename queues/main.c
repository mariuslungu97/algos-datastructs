#include <limits.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "queue.h"

void print_int_arr(int *arr, int size) {
  printf("\nARRAY: \n");
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

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

void test_linked_list() {
  LinkedList *list = linked_list();
  assert(empty_linked_list(list) == 1);
  int to_add_size = 100;
  int *to_add = generate_int_arr(to_add_size, 1, 100);
  for (int i = 0; i < to_add_size; i++) {
    push_back(list, to_add[i]);
  }
  assert(list->size == to_add_size);
  for (int i = 0; i < to_add_size; i++) {
    assert(list->size == to_add_size - i);
    int popped = pop_front(list);
    printf("Popped %d from list...\n", popped);
    assert(popped = to_add[i]);
  }
}

void test_circular_buffer() {
  CircularBuffer *buff = circular_buffer(100);
  assert(empty_buffer(buff) == 1);
  assert(full_buffer(buff) == 0);
  int to_add_size = 100;
  int *to_add = generate_int_arr(to_add_size, 1, 100);
  for (int i = 0; i < to_add_size; i++) {
    write_value(buff, to_add[i]);
  }
  assert(full_buffer(buff) == 1);
  write_value(buff, 300); // must print error since buffer is full
  for (int i = 0; i < to_add_size; i++) {
    int read = read_value(buff);
    printf("Read %d from buffer ...\n", read);
    assert(read == to_add[i]);
  }
}

void test_linked_queue() {
  LinkedQueue *queue = linked_queue();
  assert(empty_linked_queue(queue) == 1);
  int to_add_size = 100;
  int *to_add = generate_int_arr(to_add_size, 1, 100);
  for (int i = 0; i < to_add_size; i++) {
    enqueue_linked(queue, to_add[i]);
  }
  printf("[LINKED_QUEUE]\n");
  for (int i = 0; i < to_add_size; i++) {
    int deque = dequeue_linked(queue);
    printf("Dequed %d from queue...\n", deque);
    assert(deque == to_add[i]);
  }
}

void test_circular_queue() {
  CircularQueue *queue = circular_queue(100);
  assert(empty_circular_queue(queue) == 1);
  int to_add_size = 100;
  int *to_add = generate_int_arr(to_add_size, 1, 100);
  for (int i = 0; i < to_add_size; i++) {
    enqueue_circular(queue, to_add[i]);
  }
  printf("[CIRCULAR_QUEUE]\n");
  assert(full_circular_queue(queue) == 1);
  for (int i = 0; i < to_add_size; i++) {
    int deque = dequeue_circular(queue);
    printf("Dequed %d from queue...\n", deque);
    assert(deque == to_add[i]);
  }
}

int main() {
  srand((unsigned int) time(NULL));
  test_linked_list();
  test_circular_buffer();
  test_linked_queue();
  test_circular_queue();
}