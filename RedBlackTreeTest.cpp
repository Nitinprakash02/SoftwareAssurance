#include <deepstate/DeepState.hpp>
using namespace deepstate;

#include "RedBlackTree.h"

TEST(RedBlackTree, InsertDeleteTest) {
    RedBlackTree tree;

    // Perform a series of random insertions and deletions
    int numOperations = DeepState_IntInRange(1, 50);  // Perform between 1 and 50 operations

    for (int i = 0; i < numOperations; i++) {
        int operation = DeepState_IntInRange(0, 1);  // Decide operation: 0 for insert, 1 for delete
        int value = DeepState_Int();  // Generate a random value to insert or delete

        if (operation == 0) {
            LOG(INFO) << "Inserting value: " << value;
            tree.insert(value);
        } else {
            LOG(INFO) << "Deleting value: " << value;
            tree.deleteNode(value);
        }

        // Validate the Red-Black properties after each operation
        ASSERT(tree.validateRBProperties()) << "Red-Black properties violated!";
    }

    // Optional: Output the final structure of the tree for debugging
    LOG(INFO) << "Final structure of the Red-Black Tree:";
    tree.printTree();

    // Optional: Check the in-order traversal output of the tree
    LOG(INFO) << "In-order traversal of the tree:";
    tree.inorder();
}
