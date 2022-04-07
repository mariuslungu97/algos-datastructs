typedef struct Node
{
  int data;
  struct Node *next;
} Node;

typedef struct
{
  int size;
  Node *head;
  Node *tail;
} LinkedList;

typedef struct
{
  int capacity;
  int *data;
  int read;
  int write;
} CircularBuffer;

typedef struct
{
  LinkedList *list;
} LinkedQueue;

typedef struct
{
  CircularBuffer *buff;
} CircularQueue;

// linked list methods
Node *linked_node(int, Node*);
LinkedList *linked_list();
int empty_linked_list(LinkedList *);
int pop_front(LinkedList *);
void push_back(LinkedList *, int);
// circular buffer methods
CircularBuffer *circular_buffer(int);
int read_value(CircularBuffer *);
void write_value(CircularBuffer *, int);
int empty_buffer(CircularBuffer *);
int full_buffer(CircularBuffer *);
// queue methods (linked and circular)
LinkedQueue *linked_queue();
void enqueue_linked(LinkedQueue *, int);
int dequeue_linked(LinkedQueue *);
int empty_linked_queue(LinkedQueue *);

CircularQueue *circular_queue(int);
void enqueue_circular(CircularQueue *, int);
int dequeue_circular(CircularQueue *);
int empty_circular_queue(CircularQueue *);
int full_circular_queue(CircularQueue *);
