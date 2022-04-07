#ifndef LINKED_LIST

#define LINKED_LIST

typedef struct Node
{
  int data;
  struct Node *next;
} Node;

typedef struct MyLinkedList
{
  int size;
  Node *head;
} MyLinkedList;

MyLinkedList *linked_list(void);
Node *head(MyLinkedList*);
int size(MyLinkedList *);
int empty(MyLinkedList *);
int value_at(MyLinkedList *, int);    // index
void push_front(MyLinkedList *, int); // value
void push_back(MyLinkedList *, int);
int pop_front(MyLinkedList *);             // removes front from linked list and return value
int pop_back(MyLinkedList *);              // same as pop_front but for back
int front(MyLinkedList *);                 // returns front value (without removing it)
int back(MyLinkedList *);                  // same as front but for list' back
void insert(MyLinkedList *, int, int);     // index, value; insert value at index
void erase(MyLinkedList *, int);           // removes node at given index
int value_n_from_end(MyLinkedList *, int); // n-th value from end using 0-based indexing
void reverse(MyLinkedList *);
int find(MyLinkedList*, int);
void remove_value(MyLinkedList *, int); // value; removes first element with this value

#endif