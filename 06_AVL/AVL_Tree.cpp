#include "AVL_Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Calculate the height of a node
int height(Node* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Create a new node with the given key
Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Perform a right rotation on a given node
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Perform a left rotation on a given node
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get the balance factor of a node
int getBalance(Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Insert a new node into the AVL tree
Node* insertNode(Node* node, int key) {
    // Perform regular BST insertion
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else // Duplicate keys not allowed
        return node;

    // Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

// Calculate the width of the tree
int getWidth(int height) {
    if (height == 1)
        return 1;
    return getWidth(height - 1) * 2 + 1;
}

// Print the tree
void printTree(int** M, Node* root, int col, int row, int height) {
    if (root == NULL)
        return;
    M[row][col] = root->key;
    printTree(M, root->left, col - pow(2, height - 2), row + 1, height - 1);
    printTree(M, root->right, col + pow(2, height - 2), row + 1, height - 1);
}

// Print the tree in a pretty format
void printPretty(Node* root) {
    int h = height(root);
    int w = getWidth(h);
    int** M = (int**)malloc(h * sizeof(int*));
    for (int i = 0; i < h; i++) {
        M[i] = (int*)malloc(w * sizeof(int));
        for (int j = 0; j < w; j++) {
            M[i][j] = 0;
        }
    }
    printTree(M, root, w / 2, 0, h);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (M[i][j] == 0)
                printf("   ");
            else
                printf("%2d ", M[i][j]);
        }
        printf("\n");
    }
}