/* Implementation of an unbalanced Binary Search Tree and an AVL Tree (insertion) in C */

typedef struct Node
{
  struct Node *left;
  struct Node *right;
  struct Node *parent;
  int value;
} Node;

typedef struct AVLNode {
  struct AVLNode *left;
  struct AVLNode *parent;
  struct AVLNode *right;
  int value;
  int height;
} AVLNode;

typedef struct BST
{
  Node *root;
} BST;

typedef struct AVL {
  AVLNode *root;
} AVL;

static Node *tree_node(Node *left, Node *right, Node *parent, int value);
static int subtree_size(Node *root);
static void print_tree(Node *root);
static int subtree_height(Node *root);
static int exists(Node *root, int value);
static Node *successor(Node *node);
static Node *predecessor(Node *node);

BST *binary_search_tree();
void insert(BST *tree, int value);
int get_node_count(BST *tree);
void print_values(BST *tree); // from min to max
void delete_tree(BST *tree);
static void free_node(Node *node);
int is_in_tree(BST *tree, int value);
int get_height(BST *tree);
int get_min(BST *tree);
int get_max(BST *tree);
void delete_value(BST *tree, int value);
int get_successor(BST *tree, int value); // returns next highest-value in tree after given value; -1 if none
int get_predecessor(BST *tree, int value);

AVLNode *avl_node(int key, AVLNode *parent);
AVLNode *right_rotate(AVLNode *x);
AVLNode *left_rotate(AVLNode *x);
int get_avl_node_height(AVLNode *node);
int get_balance(AVLNode *node);
AVLNode *insert_avl_node(AVLNode *node, int key);
void insert_avl(AVL *tree, int value);
