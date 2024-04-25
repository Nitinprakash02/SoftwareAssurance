#include <deepstate/DeepState.hpp>
using namespace deepstate;

#include "RedBlackTree.h"

void randomInsertDeleteTest(RedBlackTree& tree) {
    int numOperations = DeepState_IntInRange(1, 30);  // Performs 1 to 30 operations
    for (int i = 0; i < numOperations; i++) {
        int operation = DeepState_IntInRange(0, 1);  // Randomly decide operation: 0 for insert, 1 for delete
        int val = DeepState_Int();
        if (operation == 0) {
            LOG(INFO) << "Inserting value: " << val;
            tree.insert(val);
        } else {
            LOG(INFO) << "Deleting value: " << val;
            tree.deleteNode(val);
        }
        ASSERT(tree.validateRBProperties()) << "Red-Black property violated after operation!";
    }
	tree.printTree();
	LOG(INFO)  << "\nIn-order traversal of the tree:\n";
    tree.inorder();
}

TEST(RedBlackTree, MixedInsertDelete) {
    RedBlackTree tree;
    randomInsertDeleteTest(tree);
}
