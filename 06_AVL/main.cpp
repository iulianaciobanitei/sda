#include "AVL_Tree.h"
#include <stdio.h>
void main()
{
	Node* root = NULL;

	root = insertNode(root, 7);
	root = insertNode(root, 8);
	root = insertNode(root, 10);
	root = insertNode(root, 5);
	root = insertNode(root, 4);
	root = insertNode(root, 6);
	root = insertNode(root, 9);

	printPretty(root);
	
	Node* to_be_deleted_root = NULL;
	to_be_deleted_root = insertNode(to_be_deleted_root, 8);
	to_be_deleted_root = insertNode(to_be_deleted_root, 6);
	to_be_deleted_root = insertNode(to_be_deleted_root, 11);
	to_be_deleted_root = insertNode(to_be_deleted_root, 5);
	to_be_deleted_root = insertNode(to_be_deleted_root, 7);
	to_be_deleted_root = insertNode(to_be_deleted_root, 10);
	to_be_deleted_root = insertNode(to_be_deleted_root, 13);
	to_be_deleted_root = insertNode(to_be_deleted_root, 4);
	to_be_deleted_root = insertNode(to_be_deleted_root, 9);
	to_be_deleted_root = insertNode(to_be_deleted_root, 12);
	to_be_deleted_root = insertNode(to_be_deleted_root, 14);

	printPretty(to_be_deleted_root);
	deleteNode(to_be_deleted_root, 7);
	printf("After deleting 7\n");
	printPretty(to_be_deleted_root);
}