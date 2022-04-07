#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "dynamic_arr.h"

MyDynamicArray *dynamic_array(voiid) {
  MyDynamicArray *arr = malloc(sizeof(MyDynamicArray));
  if (arr == NULL) {
    printf("ERROR! Memory for dynamic array not allocated ... returning NULL!\n");
    return NULL;
  }
  arr->size = 0;
  arr->capacity = 16;
  int *arr_elements = malloc(sizeof(arr->elements) * arr->capacity);
  arr->elements = arr_elements;
  return arr;
}

static void resize(MyDynamicArray *arr, int new_capacity) {
  if (new_capacity < 0) {
    printf("ERROR! The provided capacity value is not allowed!\n");
    return;
  }
  int *new_elements = malloc(sizeof(arr->elements) * new_capacity);
  if (new_elements == NULL) {
    printf("ERROR! Memory for dynamic array not allocated\n");
    return;
  }
  for (int i = 0; i < arr->size; i++) {
    *(new_elements + i) = *(arr->elements + i);
  }
  free(arr->elements);
  arr->capacity = new_capacity;
  arr->elements = new_elements;
}

int size(MyDynamicArray *arr) {
  return arr->size;
}

int capacity(MyDynamicArray *arr) {
  return arr->capacity;
}

int *elements(MyDynamicArray *arr) {
  return arr->elements;
}

int is_empty(MyDynamicArray *arr) {
  return (arr->size == 0);
}

int at(MyDynamicArray *arr, int index) {
  if (index < 0 || index >= arr->size) {
    printf("ERROR! [AT] INDEX OUT OF BOUNDS ... RETURNING VERY HIGH INT\n");
    return INT_MAX;
  }
  return *(arr->elements + index);
}

void push(MyDynamicArray *arr, int item) {
  if (arr->size + 1 > arr->capacity) {
    resize(arr, arr->capacity * 2);
  }
  *(arr->elements + arr->size) = item;
  arr->size += 1;
}

void insert(MyDynamicArray *arr, int index, int item) {
  if (index < 0 || index >= arr->size) {
    printf("ERROR! [INSERT] INDEX OUT OF BOUNDS\n");
    return;
  }
  if (arr->size + 1 > arr->capacity) {
    resize(arr, arr->capacity * 2);
  }
  for (int i = arr->size; i > index; i--) {
    *(arr->elements + i) = *(arr->elements + (i - 1));
  }
  *(arr->elements + index) = item;
  arr->size += 1;
}

void prepend(MyDynamicArray *arr, int item) {
  insert(arr, 0, item);
}

void delete_at(MyDynamicArray *arr, int index) {
  if (index < 0 || index >= arr->size) {
    printf("ERROR! [DELETE_AT] INDEX OUT OF BOUNDS\n");
    return;
  }
  for (int i = index; i < arr->size - 1; i++) {
    *(arr->elements + i) = *(arr->elements + i + 1);
  }
  arr->size -= 1;
  if (arr->size <= arr->capacity / 4) {
    resize(arr, arr->capacity / 4);
  }
}

int find(MyDynamicArray *arr, int item) {
  for (int i = 0; i < arr->size; i++) {
    if (item == *(arr->elements + i)) {
      return i;
    }
  }
  return -1;
}


void delete_item(MyDynamicArray *arr, int item) {
  int found = find(arr, item);
  if (found == -1)
    return;
  delete_at(arr, found);
}
