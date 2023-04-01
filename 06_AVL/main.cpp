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

}