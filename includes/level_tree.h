#ifndef __LEVEL_TREE_H__
#define __LEVEL_TREE_H__

enum drawline_center { C_LEFT, C_CENTER, C_RIGHT };

struct level_node_s {
  int data;
  int is_empty;
  int has_left;
  int has_right;
  struct level_node_s *next;
};
typedef struct level_node_s level_node_t;

struct level_s {
  int depth;
  int height;
  struct level_node_s *nodes;
};
typedef struct level_s level_t;

level_node_t *level_node_create(int data, int is_empty, int has_left,
                                int has_right);
level_node_t *level_node_insert(level_node_t *root, int data, int empty,
                                int has_left, int has_right);

level_t *level_create(int depth, int height);
void level_insert(level_t *level, int data);
void level_insert_custom(level_t *level, int data, int has_left, int has_right);
void level_insert_empty(level_t *level);
void level_free(level_t *level);

void level_print(level_t *level);

#endif
