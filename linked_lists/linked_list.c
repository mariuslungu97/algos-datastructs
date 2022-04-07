#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "linked_list.h"

/* Implementation of Linked List without tail pointer */

Node *list_node(int data, Node *nextptr) {
  Node *l_node = malloc(sizeof(Node));
  if (l_node == NULL) {
    printf("ERROR! Memory for Linked List Node not allocated ... returning NULL!\n");
    return NULL;
  }
  l_node->data = data;
  l_node->next = nextptr;
  return l_node;
}

MyLinkedList *linked_list() {
  MyLinkedList *l_list = malloc(sizeof(MyLinkedList));
  if (l_list == NULL) {
    printf("ERROR! Memory for linked List not allocated ... returning NULL!\n");
    return NULL;
  }
  l_list->size = 0;
  l_list->head = NULL;
  return l_list;
}

Node *head(MyLinkedList *list) {
  return list->head;
}

int size(MyLinkedList *list) {
  return (list->size);
}

int empty(MyLinkedList *list) {
  return (list->size == 0);
}

int value_at(MyLinkedList *list, int index) {
  if (list->size == 0) {
    printf("ERROR! [VALUE_AT] The list is empty ... returning very high int!\n");
    return INT_MAX;
  }

  if (index < 0 || index >= list->size) {
    printf("ERROR! [VALUE_AT] Index out of bounds ... returning very high int|\n");
    return INT_MAX;
  }

  int c = 0;
  for (Node *l_node = list->head; l_node != NULL; l_node = l_node->next) {
    if (index == c) {
      return l_node->data;
    }
    c += 1;
  }
  return INT_MAX;
}

void push_front(MyLinkedList *list, int value) {
  Node *new_node = list_node(value, list->head);
  if (new_node == NULL)
    return;
  
  list->head = new_node;
  list->size += 1;
}

void push_back(MyLinkedList *list, int value) {
  Node *new_node = list_node(value, NULL);
  if (new_node == NULL)
    return;
  
  list->size += 1;
  if (list->head == NULL) {
    list->head = new_node;
    return;
  }
  Node *l_node = list->head;
  while (l_node->next != NULL) {
    l_node = l_node->next;
  }
  l_node->next = new_node;
}

// removes front from linked list and return value
int pop_front(MyLinkedList *list) {
  if (list->size == 0) {
    printf("You should add elements before trying to pop them off ... returning very high int value!\n");
    return INT_MAX;
  }
  Node *popped = list->head;
  list->head = popped->next;
  list->size -= 1;
  int data = popped->data;
  free(popped);
  return data;
} 

// same as pop_front but for back
// TODO: review once again
int pop_back(MyLinkedList *list) {
  if (list->size == 0) {
    printf("You should add elements before trying to pop them off ... returning very high int value!\n");
    return INT_MAX;
  }
  Node *prev = NULL, *last = list->head;
  while (last->next != NULL) {
    prev = last;
    last = last->next;
  }
  if (list->size == 1)
    list->head = NULL;
  else prev->next = NULL;
  int data = last->data;
  list->size -= 1;
  free(last);
  return data;
} 

// returns front value (without removing it)
int front(MyLinkedList *list) {
  if (list->size == 0) {
    printf("There are no elements in the list ... returning very high int value!\n");
    return INT_MAX;
  }
  return (list->head->data);
} 

// same as front but for list' back
int back(MyLinkedList *list) {
  if (list->size == 0) {
    printf("There are no elements in the list ... returning very high int value!\n");
    return INT_MAX;
  }
  Node *last = list->head;
  while (last->next != NULL) {
    last = last->next;
  }
  return (last->data);
}        

// index, value; insert value at index
void insert(MyLinkedList *list, int index, int value) {
  if (index < 0 || index >= list->size) {
    printf("ERROR! [INSERT] Index out of bounds!\n");
    return;
  }
  if (index == 0) {
    Node *next = list->head;
    Node *new_node = list_node(value, next);
    list->head = new_node;
  }
  else {
    Node *prev = NULL, *current = list->head;
    int c = 0;
    while (current->next != NULL) {
      if (c == index)
        break;
      
      prev = current;
      current = current->next;
      c += 1;
    }
    Node *new_node = list_node(value, current);
    prev->next = new_node;
  }
  list->size += 1;
}

// removes node at given index
void erase(MyLinkedList *list, int index) {
  if (index < 0 || index >= list->size) {
    printf("ERROR! [INSERT] Index out of bounds!\n");
    return;
  }
  if (index == 0) {
    Node *erased = list->head;
    list->head = erased->next;
    free(erased);
  } 
  else {
    int c = 0;
    Node *prev = NULL, *erased = list->head;
    while (erased->next != NULL) {
      if (c == index) {
        break;
      }
      prev = erased;
      erased = erased->next;
    }
    prev->next = erased->next;
    free(erased);
  }
  list->size -= 1;
}

// n-th value from end using 0-based indexing
int value_n_from_end(MyLinkedList *list, int index) {
  if (index < 0 || index >= list->size) {
    printf("ERROR! [VALUE_N_FROM_END] Index out of bounds ... returning very high int!\n");
    return INT_MAX;
  }
  if (list->size == 0) {
    return INT_MAX;
  }
  int c = 0;
  for (Node *l_node = list->head; l_node != NULL; l_node = l_node->next) {
    if (index == c) {
      return l_node->data;
    }
    c += 1;
  }
  return INT_MAX;
}

void reverse(MyLinkedList *list) {
  /*
    head -> Node1 -> Node2 -> Node3 -> NULL
    head -> Node3 -> Node2 -> Node1 -> NULL
    starting from the second node to the n-th node, the current node now points to the prev node
    additionaly, the first node now points to NULL, while the head points to the last node
  */
  if (list->size == 0 || list->size == 1) {
    printf("[REVERSE] There are insufficient elements in the list for reversal!\n");
    return;
  }

  Node *prev = list->head, *l_node = list->head->next;
  list->head->next = NULL;
  while (l_node != NULL) {
    Node *temp_next = l_node->next;
    l_node->next = prev;
    prev = l_node;
    l_node = temp_next;
  }
  list->head = prev;
}

// finds first element with value; returns -1 if not found
int find(MyLinkedList *list, int value) {
  if (list->size == 0) {
    return -1;
  }
  int index = 0;
  Node *it = list->head;
  while (it != NULL) {
    if (it->data == value) {
      return index;
    }
    index += 1;
    it = it->next;
  }
  return -1;
}

// value; removes first element with this value
void remove_value(MyLinkedList *list, int value) {
  int found_index = find(list, value);
  if (found_index == -1)
    return;
  erase(list, found_index);
} 
