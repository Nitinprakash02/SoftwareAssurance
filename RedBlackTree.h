#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>
#include <string>

struct Node {
    int data;
    Node* parent;
    Node* left;
    Node* right;
    bool color;  // Red = 0, Black = 1

    Node(int data);
};

class RedBlackTree {
private:
    Node* root;
    Node* NIL;

    void leftRotate(Node* x);
    void rightRotate(Node* x);
    void fixInsert(Node* k);
    void fixDelete(Node* x);
    void rbTransplant(Node* u, Node* v);
    void deleteNodeHelper(Node* node, int key);
    Node* minimum(Node* node);
    Node* maximum(Node* node);
    void inOrderHelper(Node* node);
    void printHelper(Node* root, std::string indent, bool last);
	bool checkRBProperties(Node* node, int blackCount, int& pathBlackCount);

public:
    RedBlackTree();
    void insert(int key);
    void deleteNode(int data);
    void printTree();
    void inorder();
	bool validateRBProperties();
	Node* getRoot() const { return root; }
};

#endif // RED_BLACK_TREE_H
