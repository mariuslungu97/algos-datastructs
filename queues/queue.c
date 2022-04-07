#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "queue.h"

/* Circular Buffer (implementation doesn't allow for overwrites) */

CircularBuffer *circular_buffer(int capacity) {
  if (capacity <= 0) {
    printf("ERROR! [CIRCULAR_BUFFER] Capacity must be greater than 0 ... returning NULL");
    return NULL;
  }
  CircularBuffer *buff = malloc(sizeof(*buff));
  if (buff == NULL) {
    printf("ERROR! [CIRCULAR_BUFFER] Buffer memory cannot be allocated ... returning NULL");
    return NULL;
  }
  buff->data = malloc((capacity + 1) * sizeof(int));
  buff->capacity = capacity + 1;
  buff->read = 0;
  buff->write = 0;
  return buff;
}

int empty_buffer(CircularBuffer *buff) {
  return (buff->read == buff->write);
}

int full_buffer(CircularBuffer *buff) {
  int next_write = (buff->write + 1) % buff->capacity; 
  if (next_write == buff->read) {
    return 1;
  } 
  return 0;
}

int read_value(CircularBuffer *buff) {
  if (empty_buffer(buff)) {
    printf("[READ_VALUE] Buffer is empty ... returning very high int value!");
    return INT_MAX;
  }
  int read_value = *(buff->data + buff->read);
  buff->read = (buff->read + 1) % buff->capacity;
  return read_value;
}

void write_value(CircularBuffer *buff, int value) {
  if (full_buffer(buff)) {
    printf("[WRITE_VALUE] Buffer is full!");
    return;
  }
  *(buff->data + buff->write) = value;
  buff->write = (buff->write + 1) % buff->capacity;
}

/* Linked List (using tail pointer) */

Node *linked_node(int data, Node *next) {
  Node *new_node = malloc(sizeof(*new_node));
  if (new_node == NULL) {
    printf("ERROR! [LINKED_NODE] Node memory cannot be allocated ... returning NULL!");
    return NULL;
  }
  new_node->data = data;
  new_node->next = next;
  return new_node;
}

LinkedList *linked_list() {
  LinkedList *list = malloc(sizeof(*list));
  if (list == NULL) {
    printf("ERROR! [LINKED_LIST] Linked List memory cannot be allocated ... returning NULL!");
    return NULL;
  }
  list->size = 0;
  list->head = NULL;
  list->tail = NULL;
  return list;
}

int empty_linked_list(LinkedList *list) {
  return (list->size == 0);
}

int pop_front(LinkedList *list) {
  if (empty_linked_list(list)) {
    printf("[POP_FRONT] List is empty ... returning very high int value!");
    return INT_MAX;
  }
  Node *popped = list->head;
  list->head = popped->next;
  if (list->size == 1) {
    list->tail = NULL;
  }
  int data = popped->data;
  list->size -= 1;
  free(popped);
  return data;
}

void push_back(LinkedList *list, int value) {
  // special case: size == 0 when head and tail point to the same node
  Node *new_node = linked_node(value, NULL);
  if (list->size == 0) {
    list->head = new_node;
    list->tail = new_node;
  } else {
    list->tail->next = new_node;
    list->tail = new_node;
  }
  list->size += 1;
}

/* Circular And Linked Queue */

LinkedQueue *linked_queue() {
  LinkedQueue *queue = malloc(sizeof(*queue));
  if (queue == NULL) {
    printf("ERROR! [LINKED_QUEUE] Linked Queue Memory cannot be allocated ... returning NULL");
    return NULL;
  }
  LinkedList *l = linked_list();
  if (l == NULL) {
    return NULL;
  }
  queue->list = l;
  return queue;
}

void enqueue_linked(LinkedQueue *queue, int value) {
  push_back(queue->list, value);
}

int dequeue_linked(LinkedQueue *queue) {
  return pop_front(queue->list);
}

int empty_linked_queue(LinkedQueue *queue) {
  return empty_linked_list(queue->list);
}

CircularQueue *circular_queue(int capacity) {
  CircularQueue *queue = malloc(sizeof(*queue));
  if (queue == NULL) {
    printf("ERROR! [LINKED_QUEUE] Linked Queue Memory cannot be allocated ... returning NULL");
    return NULL;
  }
  CircularBuffer *b = circular_buffer(capacity);
  if (b == NULL) {
    return NULL;
  }
  queue->buff = b;
  return queue;
}

void enqueue_circular(CircularQueue *queue, int value) {
  write_value(queue->buff, value);
}

int dequeue_circular(CircularQueue *queue) {
  return read_value(queue->buff);
}

int empty_circular_queue(CircularQueue *queue) {
  return empty_buffer(queue->buff);
}

int full_circular_queue(CircularQueue *queue) {
  return full_buffer(queue->buff);
}




