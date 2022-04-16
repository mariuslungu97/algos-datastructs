#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "bst.h"

int max(int a, int b) {
  return (a > b) ? a : b;
}

BST *binary_search_tree() {
  BST *tree = malloc(sizeof(*tree));
  if (tree == NULL) {
    printf("ERROR! [BINARY_SEARCH_TREE] Struct memory cannot be allocated ... returning NULL!");
    return NULL;
  }
  tree->root = NULL;
  return tree;
}

static Node *tree_node(Node *left, Node *right, Node *parent, int value) {
  Node *new_node = malloc(sizeof(*new_node));
  if (new_node == NULL) {
    printf("ERROR! [TREE_NODE] Struct memory cannot be allocated ... returning NULL");
    return NULL;
  }
  new_node->left = left;
  new_node->right = right;
  new_node->parent = parent;
  new_node->value = value;

  return new_node;
}

static int subtree_size(Node *root) {
  if (root == NULL)
    return 0;

  return 1 + subtree_size(root->left) + subtree_size(root->right);
}

static int subtree_height(Node *root) {
  if (root == NULL)
    return 0;

  return 1 + max(subtree_height(root->left), subtree_height(root->right));
}

static Node *subtree_first(Node *node) {
  if (node == NULL)
    return NULL;
  
  while (node->left != NULL)
    node = node->left;

  return node;
}

static Node *subtree_last(Node *node) {
  if (node == NULL)
    return NULL;

  while (node->right != NULL)
    node = node->right;

  return node;
}

static Node *find(Node *root, int value) {
  if (root == NULL)
    return NULL;

  if (value == root->value)
    return root;
  else if (value < root->value)
    return find(root->left, value);
  else
    return find(root->right, value);
}

static void print_tree(Node *root) {
  if (root != NULL) {
    print_tree(root->left);
    printf("Value: %d\n", root->value);
    print_tree(root->right);
  }
}

static void free_node(Node *node) {
  if (node != NULL) {
    free_node(node->left);
    free_node(node->right);
    free(node);
  }
}

static int exists(Node *root, int value) {
  if (root == NULL)
    return 0;

  if (value == root->value)
    return 1;
  else if (value < root->value)
    return exists(root->left, value);
  else
    return exists(root->right, value);
}

static Node *successor(Node *node) {
  if (node == NULL)
    return NULL;

  if (node->right != NULL) {
    return subtree_first(node->right);
  }
  else {
    Node *next = node->parent;
    while (next != NULL && next->left != node) {
      node = next;
      next = next->parent;
    }

    if (next == NULL)
      return NULL;

    return next;
  }
}

static Node *predecessor(Node *node) {
  if (node == NULL)
    return NULL;

  if (node->left != NULL) {
    return subtree_last(node->left);
  }
  else {
    Node *next = node->parent;
    while (next != NULL && next->right != node) {
      node = next;
      next = next->parent;
    }

    if (next == NULL)
      return NULL;

    return next;
  }
}

static void delete_node(Node *node) {
  if (node->left == NULL && node->right == NULL) {
    Node *parent = node->parent;
    if (parent->left == node)
      parent->left = NULL;
    else
      parent->right = NULL;
    free(node);
  }
  else {
    if (node->left != NULL) {
      Node *pred = predecessor(node);
      int temp = pred->value;
      pred->value = node->value;
      node->value = temp;
      delete_node(pred);
    }

    if (node->right != NULL) {
      Node *succ = successor(node);
      int temp = succ->value;
      succ->value = node->value;
      node->value = temp;
      delete_node(succ);
    }
  }
}

void insert(BST *tree, int value) {
  Node *new_node;
  if (tree->root == NULL) {
    new_node = tree_node(NULL, NULL, NULL, value);
    if (new_node != NULL) {
      tree->root = new_node;
      return;
    }
  }
  else {
    Node *prev = NULL, *it = tree->root;
    while (it != NULL) {
      prev = it;
      it = (value < it->value) ? it->left : it->right;
    }
    new_node = tree_node(NULL, NULL, prev, value);
    if (value < prev->value) {
      prev->left = new_node;
    } else {
      prev->right = new_node;
    }
  }
}

int get_node_count(BST *tree) {
  if (tree->root == NULL)
    return 0;
  
  return subtree_size(tree->root);
}

void print_values(BST *tree) {
  if (tree->root == NULL)
    return;

  print_tree(tree->root);
}

void delete_tree(BST *tree) {
  if (tree->root == NULL)
    return;

  free_node(tree->root);
  tree->root = NULL;
}

int is_in_tree(BST *tree, int value) {
  if (tree->root == NULL)
    return 0;

  return exists(tree->root, value);
}

int get_height(BST *tree) {
  if (tree->root == NULL)
    return 0;
  
  return subtree_height(tree->root);
}

int get_min(BST *tree) {
  if (tree->root == NULL)
    return INT_MAX;

  Node *it = tree->root;
  while (it->left != NULL)
    it = it->left;

  return it->value;
}

int get_max(BST *tree) {
  if (tree->root == NULL)
    return INT_MIN;

  Node *it = tree->root;
  while (it->right != NULL)
    it = it->right;

  return it->value;
}

void delete_value(BST *tree, int value) {
  if (tree->root == NULL)
    return;
  Node *node_value = find(tree->root, value);
  if (node_value == NULL)
    return;
  
  delete_node(node_value);
}

int get_successor(BST *tree, int value) {
  if (tree->root == NULL)
    return INT_MIN;

  Node *node_value = find(tree->root, value);
  if (node_value == NULL)
    return INT_MIN;

  Node *succ = successor(node_value);
  if (succ == NULL)
    return INT_MIN;
  
  return succ->value;
}

int get_predecessor(BST *tree, int value) {
  if (tree->root == NULL)
    return INT_MAX;

  Node *node_value = find(tree->root, value);
  if (node_value == NULL)
    return INT_MAX;

  Node *pred = predecessor(node_value);
  if (pred == NULL)
    return INT_MAX;
  
  return pred->value;
}

AVLNode *avl_node(int key, AVLNode *parent) {
  AVLNode *new_node = malloc(sizeof(*new_node));
  if (new_node == NULL) {
    printf("ERROR! [AVL_NODE] Struct memory cannot be allocated ... returning NULL");
    return NULL;
  }
  new_node->value = key;
  new_node->height = 1;
  new_node->parent = parent;
  new_node->right = NULL;
  new_node->left = NULL;
  return new_node;
}

int get_avl_node_height(AVLNode *node) {
  if (node == NULL)
    return 0;

  return node->height;
}

int get_balance(AVLNode *node) {
  if (node == NULL)
    return 0;

  return get_avl_node_height(node->left) - get_avl_node_height(node->right);
}

AVLNode *left_rotate(AVLNode *x) {
  AVLNode *y = x->right; // new root
  AVLNode *T2 = y->left; 
  // perform rotation
  y->parent = x->parent;
  x->parent = y;
  x->right = T2;
  y->left = x;
  // update heights
  y->height = max(get_avl_node_height(y->left), get_avl_node_height(y->right)) + 1;
  x->height = max(get_avl_node_height(x->left), get_avl_node_height(x->right)) + 1;
  // return new root
  return y;
}

AVLNode *right_rotate(AVLNode *x) {
  AVLNode *y = x->left;
  AVLNode *T2 = y->right;

  y->parent = x->parent;
  x->parent = y;
  y->right = x;
  x->left = T2;

  y->height = max(get_avl_node_height(y->left), get_avl_node_height(y->right)) + 1;
  x->height = max(get_avl_node_height(x->left), get_avl_node_height(x->right)) + 1;

  return y;
}

AVLNode *insert_avl_node(AVLNode *node, int key) {
  if (node == NULL)
    return avl_node(key, node);

  if (key < node->value)
    node->left = insert_avl_node(node->left, key);
  else if (key > node->value)
    node->right = insert_avl_node(node->right, key);
  else 
    return node;

  node->height = 1 + max(get_avl_node_height(node->left), get_avl_node_height(node->right));
  int balance = get_balance(node);

  if (balance > 1 && key < node->left->value)
    return right_rotate(node);
  
  if (balance < -1 && key > node->right->value)
    return left_rotate(node);
  
  if (balance > 1 && key > node->left->value) {
    node->left = left_rotate(node);
    return right_rotate(node);
  }

  if (balance < -1 && key < node->right->value) {
    node->right = right_rotate(node);
    return left_rotate(node);
  }

  return node;
}

void insert_avl(AVL *tree, int value) {
  tree->root = insert_avl_node(tree->root, value);
}