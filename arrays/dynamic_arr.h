#ifndef DYNAMIC_ARR_H

#define DYNAMIC_ARR_H

typedef struct MyDynamicArray
{
  int size;
  int capacity;
  int *elements;
} MyDynamicArray;

MyDynamicArray *dynamic_array(void); // generates dynamic array on heap
int size(MyDynamicArray*);
int capacity(MyDynamicArray*);
int is_empty(MyDynamicArray*);
int *elements(MyDynamicArray*);
int at(MyDynamicArray*, int);
void push(MyDynamicArray*, int);
void insert(MyDynamicArray*, int, int); // index, item
void prepend(MyDynamicArray*, int);     // item
void delete_at(MyDynamicArray*, int);   // index
void delete_item(MyDynamicArray*, int); // item
int find(MyDynamicArray*, int);         // item
static void resize(MyDynamicArray*, int);

#endif