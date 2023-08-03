#include "includes/level_tree.h"
#include "includes/binary_tree.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int power(int a, int p) {
	int count = 1;

	for (; p; p--)
		count *= a;
	return count;
}

unsigned int height(node_t *root) {
	unsigned int l = 0, r = 0;

	if (root == NULL)
		return 0;
	l = root->left ? height(root->left): 0;
	r = root->right ? height(root->right) : 0;

	return 1 + (l > r ? l : r);
}

void tree_dig_level(node_t *root, level_t *level, int depth) {
	if (!level)
		return;

	if (depth && root) {
		tree_dig_level(root->left, level, depth - 1);
		tree_dig_level(root->right, level, depth - 1);
		return;
	}

	if (!root) 
		level_insert_empty(level);
	else
		level_insert_custom(level, root->data, root->left != NULL,
											root->right != NULL);
}

void tree_print(node_t *root) {
	uint h, i;

	if (root == NULL)
		return;

	h = height(root);
	for (i = 0; i < h; i++) {
		level_t *level = level_create(i, h);

		if (!level)
			break;

		tree_dig_level(root, level, i);
		level_print(level);
		level_free(level);
	}
}

/*
* columns = 15
* depth = 3
* inner_padding = round(columns / (2 ^ depth))
* outer_padding = inner_padding / 2
*
* d = 0, ip = 15, op = 7
* d = 1, ip = 7, op = 3
* d = 2, ip = 3, op = 1
* d = 3, ip = 1, op = 0
*
*
*
*
*                                     (000)
*                 (000)                                   (000)
*       (000)               (000)               (000)              (000)
*  (000)     (000)     (000)     (000)     (000)     (000)     (000)     (000)
*
*
*
*/

level_node_t *level_node_create(int data, int is_empty, int left, int right) {
	level_node_t *node = malloc(sizeof(level_node_t));

	if (!node)
		return NULL;

	node->data = data;
	node->is_empty = is_empty;
	node->has_left = left;
	node->has_right = right;
	node->next = NULL;

	return node;
}

level_node_t *level_node_insert(level_node_t *root, int data, int empty,
																int left, int right) {
	if (!root)
		return level_node_create(data, empty, left, right);

	root->next = level_node_insert(root->next, data, empty, left, right);
	return root;
}

level_t *level_create(int depth, int height) {
	level_t *node = malloc(sizeof(level_t));

	if (!node)
		return NULL;

	node->depth = depth;
	node->height = height;
	node->nodes = NULL;

	return node;
}

void level_free(level_t *level) {
	level_node_t *node = NULL, *tmp = NULL;

	if (!level)
		return;

	for (node = level->nodes; node; node = tmp) {
		tmp = node->next;
		free(node);
	}
	
	free(level);
}

void level_insert(level_t *level, int data) {
	level_insert_custom(level, data, 1, 1);
}

void level_insert_custom(level_t *level, int data, int has_left,
												 int has_right) {
	if (!level)
		return;

	level->nodes = level_node_insert(level->nodes, data, 0, has_left, has_right);
}

void level_insert_empty(level_t *level) {
	if (!level)
		return;

	level->nodes = level_node_insert(level->nodes, 0, 1, 0, 0);
}


void drawline(char a, char b, char c, int size, int center) {
	int i;

	center = center < 0 ? 0 : center > size ? size : center;
	for (i = 0; i < size; ++i)
			putchar(i < center ? a : i > center ? c : b);
}

void drawlinec(char a, char b, char c, int size, enum drawline_center center) {
	int val = 0;

	switch (center) {
		case C_LEFT:
			val = 0;
			break;
		case C_RIGHT:
			val = size;
			break;
		case C_CENTER:
			val = size / 2;
			break;
	}

	drawline(a, b, c, size, val);
}

void dupchar(char c, int size) {
	drawline(c, c, c, size, 0);
}

void calculate_props(level_t *level, int spacing, int *padding) {
	int columns = power(2, level->height - 1) * 2 - 1;

	*padding = columns / power(2, level->depth) / 2 * spacing;
}

void print_arm(int size, int is_left) {
	int m = size / 2, i = is_left ? 0 : size - 1;
	int step = is_left ? 1 : -1;

	for (; is_left ? i < size : i >= 0; i += step)
		putchar(i < m ? ' ' : i > m ? '-' : '.');
}

void level_print(level_t *level) {
	level_node_t *node = NULL;
	int padding, spacing = 5;

	if (!level)
		return;

	calculate_props(level, spacing, &padding);

	for (node = level->nodes; node; node = node->next) {
		if (node->is_empty) {
			dupchar(' ', spacing + padding * 2 + (node->next ? spacing : 0));
			continue;
		}
		/* before node */
		drawlinec(' ', '.', '-', padding, node->has_left ? C_CENTER : C_RIGHT);


		/* node */
		printf("(%03d)", node->data);
	
		/* after node */
		if (node->has_right)
			drawlinec('-', '.', ' ', padding, C_CENTER);
		else
			dupchar(' ', padding);

		/* between nodes */
		if (node->next)
			dupchar(' ', spacing);
	}
	

	putchar(10);
}
