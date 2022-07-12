#include <stdio.h>
#include <stdlib.h>

typedef struct _bst_node {
	int data;
	struct _bst_node* left;
	struct _bst_node* right;
} BstNode;

// tracking allocated BstNodes with array
BstNode** _allocated;
int _alloc_size = 0;

BstNode* CreateNode(int data) {
	_alloc_size++;
	if (_allocated == NULL) {
		// create array
		_allocated = (BstNode**) malloc(_alloc_size * sizeof(BstNode*));

	} else {
		// expand array
		_allocated = (BstNode**) realloc(_allocated, _alloc_size * sizeof(BstNode*));
	}

	if (_allocated == NULL) {
		printf("Allocation error\n");
		exit(1);
	}

	BstNode* node = (BstNode*) malloc(sizeof(BstNode));
	node->data = data;

	// add node to _allocated array
	int id = _alloc_size - 1;
	*(_allocated + id) = node;
	
	return node;
}

BstNode* Insert(BstNode* root, int data) {
	BstNode* node = CreateNode(data);
	if (root == NULL) root = node;
	else {
		if (data <= root->data) root->left = node;
		else root->right = node;
	}

	return node;
}

void DestroyNodes() {
	for (int i = 0; i < _alloc_size; i += 1) {
		BstNode* node = *(_allocated + i);
		free(node);
	}
}

void DestroyAllocated() {
	free(_allocated);
}


BstNode* CreateTree() {
	// Create root node
	BstNode* root = CreateNode(10);
	BstNode* node = root;
	BstNode* left;
	BstNode* right;
	// Create child nodes
	left = Insert(node, 5);
	Insert(left, 23);
	right = Insert(node, 17);
	Insert(right, 41);
	node = Insert(right, 11);
	Insert(node, 39);

	return root;
}

void DisplayTree(BstNode* root) {
	if (_allocated == NULL) {
		printf("Binary tree does not exist\n");
		exit(1);
	}

	if (root == NULL) {
		return;
	}
	
	BstNode* left = root->left;
	BstNode* right = root->right;

	printf("(%d) ", root->data);

	if (left != NULL) {
		printf("L ");
		printf("{ ");
		DisplayTree(left);
		printf(" } ");
	}
	if (right != NULL) {
		printf("R ");
		printf("{ ");
		DisplayTree(right);
		printf(" } ");
	}
}

void DisplayAlloc() {
	if (_allocated == NULL) {
		printf("Binary tree does not exist\n");
		exit(1);
	}

	for (int i = 0; i < _alloc_size; i += 1) {
		BstNode* node = *(_allocated + i);

		printf(i < _alloc_size - 1 ? "(%d) " : "(%d)", node->data);
	}
}


int main() {
	BstNode* root = CreateTree();
	printf("Binary tree: ");
	DisplayTree(root);
	//printf("\n");
	//DisplayAlloc();
	printf("\n");

	// do not forget to free memory
	DestroyNodes();
	DestroyAllocated();

	return 0;
}

