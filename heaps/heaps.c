#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "heaps.h"

static void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

static int parent(int i) {
  return (i + 1) / 2 - 1;
}

static int left(int i) {
  return (i + 1) * 2 - 1;
}

static int right(int i) {
  return (i + 1) * 2;
}

Heap *heap(int capacity) {
  Heap *new_heap = malloc(sizeof(*new_heap));
  if (new_heap == NULL) {
    printf("ERROR! [HEAP] Struct memory cannot be allocated ... returning NULL!\n");
    return NULL;
  }
  int *heap_arr = malloc(capacity * sizeof(*heap_arr));
  if (heap_arr == NULL) {
    printf("ERROR! [HEAP] Array memory cannot be allocated ... returning NULL!\n");
    return NULL;
  }
  new_heap->capacity = capacity;
  new_heap->size = 0;
  new_heap->heap_arr = heap_arr;
  return new_heap;
}

static void sift_up(int *heap_arr, int index) {
  int i = index;
  while (i > 0 && *(heap_arr + parent(i)) < *(heap_arr + i)) {
    swap(heap_arr + parent(i), heap_arr + i);
    i = parent(i);
  }
}

static void sift_down(int *heap_arr, int size, int index) {
  int i = index;
  while (i < size) {
    int maxIndex = i;
    if (left(i) < size && *(heap_arr + left(i)) > *(heap_arr + maxIndex))
      maxIndex = left(i);

    if (right(i) < size && *(heap_arr + right(i)) > *(heap_arr + maxIndex))
      maxIndex = right(i);

    if (i != maxIndex) {
      swap(heap_arr + i, heap_arr + maxIndex);
      i = maxIndex;
    }
    else break;
  }  
}

int is_empty(Heap *heap) {
  return (heap->size == 0);
}

int extract_max(Heap *heap) {
  if (heap->size <= 0) return INT_MIN;
  int result = *(heap->heap_arr + 0);
  swap(heap->heap_arr, heap->heap_arr + heap->size - 1);
  heap->size -= 1;
  sift_down(heap->heap_arr, heap->size, 0);
  return result;
}

void remove_at(Heap *heap, int index) {
  if (heap->size <= 0) return;
  if (index < heap->size - 1) return;
  *(heap->heap_arr + index) = INT_MAX;
  sift_up(heap->heap_arr, index);
  extract_max(heap);
}

void insert(Heap *heap, int value) {
  if (heap->size + 1 > heap->capacity) {
    printf("ERROR! [INSERT] Heap is full\n!");
    return;
  }
  *(heap->heap_arr + heap->size) = value;
  sift_up(heap->heap_arr, heap->size);
  heap->size += 1;
}

Heap *heapify(int *arr, int size) {
  Heap *new_heap = malloc(sizeof(*new_heap));
  if (new_heap == NULL) {
    printf("ERROR! [HEAPIFY] Struct memory cannot be allocated ... return NULL!\n");
    return NULL;
  }
  for (int i = size / 2 - 1; i >= 0; i--) {
    sift_down(arr, size, i);
  }

  new_heap->capacity = size;
  new_heap->size = size;
  new_heap->heap_arr = arr;
  return new_heap;
}

void heap_sort(int *arr, int size) {
  Heap *heap = heapify(arr, size);
  for (int i = 0; i < size; i++) {
    swap(arr + 0, arr + heap->size - 1);
    heap->size -= 1;
    sift_down(heap->heap_arr, heap->size, 0);
  }
}