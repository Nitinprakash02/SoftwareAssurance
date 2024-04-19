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
    bool y_original_color = y->color;
    if (z->left == NIL) {
        x = z->right;
        rbTransplant(z, z->right);
    }
    else if (z->right == NIL) {
        x = z->left;
        rbTransplant(z, z->left);
    }
    else {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent != z) {
            rbTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (!y_original_color) {
        fixDelete(x);
    }
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

void RedBlackTree::fixDelete(Node* x) {
    while (x != root && x->color == 1) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == 0) {
                w->color = 1;
                x->parent->color = 0;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == 1 && w->right->color == 1) {
                w->color = 0;
                x = x->parent;
            }
            else {
                if (w->right->color == 1) {
                    w->left->color = 0;
                    w->color = 1;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = 1;
                w->right->color = 1;
                leftRotate(x->parent);
                x = root;
            }
        }
        else {
            Node* w = x->parent->left;
            if (w->color == 0) {
                w->color = 1;
                x->parent->color = 0;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == 1 && w->left->color == 1) {
                w->color = 0;
                x = x->parent;
            }
            else {
                if (w->left->color == 1) {
                    w->right->color = 0;
                    w->color = 1;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = 1;
                w->left->color = 1;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = 1;
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

Node* RedBlackTree::minimum(Node* node) {
    while (node->left != NIL) {
        node = node->left;
    }
    return node;
}

Node* RedBlackTree::maximum(Node* node) {
    while (node->right != NIL) {
        node = node->right;
    }
    return node;
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

// Checks if the node is red
bool isRed(Node* node) {
    return node != nullptr && node->color == 0;  // Assuming red is represented by 0
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

bool validateRBTreeProperties(Node* node, int blackCount, int& pathBlackCount) {
    if (node == nullptr) {
        if (pathBlackCount == -1) {
            pathBlackCount = blackCount;
        }
        return pathBlackCount == blackCount;
    }

    if (node->color == 1) { // Assuming 1 is black
        ++blackCount;
    } else if (isRed(node)) {
        if (isRed(node->left) || isRed(node->right)) {
            return false; // Red violation
        }
    }

    return validateRBTreeProperties(node->left, blackCount, pathBlackCount) &&
           validateRBTreeProperties(node->right, blackCount, pathBlackCount);
}

bool validateRedBlackTree(RedBlackTree& tree) {
    int pathBlackCount = -1;
    return tree.getRoot() != nullptr && 
           tree.getRoot()->color == 1 &&  // root must be black
           validateRBTreeProperties(tree.getRoot(), 0, pathBlackCount);
}

/*
int main() {
    RedBlackTree bst;
    // Inserting nodes
    bst.insert(8);
    bst.insert(18);
    bst.insert(5);
    bst.insert(15);
    bst.insert(17);
    bst.insert(25);
    bst.insert(40);
    bst.insert(80);

    // Printing the Red-Black Tree structure
    std::cout << "Initial Red-Black Tree:" << std::endl;
    bst.printTree();

    // In-order traversal of the tree
    std::cout << "Inorder traversal before deletion:" << std::endl;
    bst.inorder();

    // Deleting a node
    bst.deleteNode(18);
    std::cout << "\nRed-Black Tree after deleting 18:" << std::endl;
    bst.printTree();

    // In-order traversal after deletion
    std::cout << "Inorder traversal after deletion:" << std::endl;
    bst.inorder();

    return 0;
}
*/