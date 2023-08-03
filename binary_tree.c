#include "includes/binary_tree.h"
#include <stdlib.h>
#include <stdio.h>

node_t *node_create(int data) {
	node_t *node = NULL;

	node = malloc(sizeof(node_t));
	if (!node)
		return NULL;

	node->data = data;
	node->left = node->right = NULL;

	return node;
}

node_t *node_insert(node_t *root, int data) {
	if (!root)
		return node_create(data);

	if (data < root->data)
		root->left = node_insert(root->left, data);
	else
		root->right = node_insert(root->right, data);

	return root;
}

static void node_print_recursive(node_t *root, int is_begin) {
	if (!root)
		return;

	printf("(");
	node_print_recursive(root->left, 0);
	if (root->left)
		printf(", ");

	if (is_begin)
		printf("[%d]", root->data);
	else
		printf("%d", root->data);

	if (root->right)
		printf(", ");

	node_print_recursive(root->right, 0);
	printf(")");

	if (is_begin)
		putchar(10);
}

void node_print(node_t *root) {
	if (!root)
		return;
	node_print_recursive(root, 1);
}
