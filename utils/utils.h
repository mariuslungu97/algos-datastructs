#ifndef UTILS_H

#define UTILS_H

void handler(int sig);
void print_int_arr(int *arr, int size, char *name);
int generate_int(int min, int max);
int *generate_int_arr(int size, int min_int, int max_int);

#endif