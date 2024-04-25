#include "RedBlackTree.h"

Node::Node(int data) : data(data), parent(nullptr), left(nullptr), right(nullptr), color(0) {}

RedBlackTree::RedBlackTree() {
    NIL = new Node(0);
    NIL->color = 1;
    NIL->left = nullptr;
    NIL->right = nullptr;
    root = NIL;
}

void RedBlackTree::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NIL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != NIL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    }
    else if (x == x->parent->right) {
        x->parent->right = y;
    }
    else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void RedBlackTree::fixInsert(Node* k) {
    Node* u;
    while (k->parent->color == 0) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            if (u->color == 0) {
                u->color = 1;
                k->parent->color = 1;
                k->parent->parent->color = 0;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }
                k->parent->color = 1;
                k->parent->parent->color = 0;
                leftRotate(k->parent->parent);
            }
        }
        else {
            u = k->parent->parent->right;
            if (u->color == 0) {
                u->color = 1;
                k->parent->color = 1;
                k->parent->parent->color = 0;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }
                k->parent->color = 1;
                k->parent->parent->color = 0;
                rightRotate(k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->color = 1;
}

void RedBlackTree::deleteNodeHelper(Node* node, int key) {
    Node* z = NIL;
    Node* x, * y;
    while (node != NIL) {
        if (node->data == key) {
            z = node;
            break;
        }
        node = node->data < key ? node->right : node->left;
    }
    if (z == NIL) {
        std::cout << "Key not found in the tree" << std::endl;
        return;
    }

    y = z;
    int y_original_color = y->color;
    if (z->left == NIL) {
        x = z->right;
        rbTransplant(z, z->right);
    }
    else if (z->right == NIL) {
        x = z->left;
        rbTransplant(z, z->left);
    }
    else {
        // Removed usage of minimum to replace z with the minimum from the right subtree
        // You will need to decide how to replace this logic, perhaps using a different method
        // Or adjust your tree handling logic to not require a replacement from the subtree
    }
    // fixDelete has been removed, so any handling of color fix-up after deletion needs to be handled differently
}

void RedBlackTree::rbTransplant(Node* u, Node* v) {
    if (u->parent == nullptr) {
        root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void RedBlackTree::printTree() {
    if (root) {
        printHelper(root, "", true);
    }
}

void RedBlackTree::printHelper(Node* root, std::string indent, bool last) {
    if (root != NIL) {
        std::cout << indent;
        if (last) {
            std::cout << "R----";
            indent += "   ";
        }
        else {
            std::cout << "L----";
            indent += "|  ";
        }

        std::string sColor = root->color ? "BLACK" : "RED";
        std::cout << root->data << "(" << sColor << ")" << std::endl;
        printHelper(root->left, indent, false);
        printHelper(root->right, indent, true);
    }
}

void RedBlackTree::inorder() {
    inOrderHelper(root);
    std::cout << std::endl;
}

void RedBlackTree::inOrderHelper(Node* node) {
    if (node != NIL) {
        inOrderHelper(node->left);
        std::cout << node->data << " ";
        inOrderHelper(node->right);
    }
}

void RedBlackTree::insert(int key) {
    Node* node = new Node(key);
    node->parent = nullptr;
    node->left = NIL;
    node->right = NIL;
    node->color = 0;

    Node* y = nullptr;
    Node* x = root;
    while (x != NIL) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }

    node->parent = y;
    if (y == nullptr) {
        root = node;
    }
    else if (node->data < y->data) {
        y->left = node;
    }
    else {
        y->right = node;
    }

    if (node->parent == nullptr) {
        node->color = 1;
        return;
    }

    if (node->parent->parent == nullptr) {
        return;
    }

    fixInsert(node);
}

void RedBlackTree::deleteNode(int data) {
    deleteNodeHelper(this->root, data);
}

bool RedBlackTree::validateRBProperties() {
    int pathBlackCount = -1;
    return this->checkRBProperties(root, 0, pathBlackCount);
}

bool RedBlackTree::checkRBProperties(Node* node, int blackCount, int& pathBlackCount) {
    if (node == nullptr) {
        if (pathBlackCount == -1) pathBlackCount = blackCount;
        return pathBlackCount == blackCount;
    }
    if (node->color == 1) blackCount++;  // Increment for black nodes
    // Add more checks as per Red-Black Tree rules

    return checkRBProperties(node->left, blackCount, pathBlackCount) &&
           checkRBProperties(node->right, blackCount, pathBlackCount);
}
