typedef struct Heap
{
  int size;
  int capacity;
  int *heap_arr;
} Heap;

static void swap(int *a, int *b);

static int parent(int i);
static int left(int i);
static int right(int i);

static void sift_up(int *heap_arr, int index);
static void sift_down(int *heap_arr, int size, int index);

Heap *heap(int capacity);
void insert(Heap *heap, int key);
int is_empty(Heap *heap);
int extract_max(Heap *heap);
void remove_at(Heap *heap, int index);
Heap *heapify(int *arr, int size);
void heap_sort(int *arr, int size);