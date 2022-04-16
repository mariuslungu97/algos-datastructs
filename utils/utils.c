
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <execinfo.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"

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
