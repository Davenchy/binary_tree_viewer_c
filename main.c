#include "includes/binary_tree.h"
#include "includes/level_tree.h"
#include <stdlib.h>

int main(void) {
	node_t *node = NULL;

	node = node_create(10);
	node->left = node_create(5);
	node->right = node_create(15);

	node->left->left = node_create(1);
	node->left->right = node_create(3);
	node->right->left = node_create(6);
	node->right->right = node_create(12);

	node->left->right->left = node_create(9);
	node->left->right->right = node_create(11);

	node->right->right->left = node_create(13);
	node->right->right->right = node_create(14);

	// node_print(node);
	tree_print(node);

	return 0;
}
