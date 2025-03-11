#pragma once


typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;



Node* insertNode(Node* node, int key);
Node* deleteNode(Node* root, int key);
void printPretty(Node* root);