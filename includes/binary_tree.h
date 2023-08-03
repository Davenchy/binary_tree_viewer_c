#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

struct node_s {
  int data;
  struct node_s *left;
  struct node_s *right;
};
typedef struct node_s node_t;

node_t *node_create(int data);
node_t *node_insert(node_t *root, int data);
void node_print(node_t *root);

void tree_print(node_t *root);

#endif
