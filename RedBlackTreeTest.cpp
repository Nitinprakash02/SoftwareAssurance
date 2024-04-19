#include <deepstate/DeepState.hpp>
using namespace deepstate;

#include "RedBlackTree.h"

void randomInsertTest(RedBlackTree& tree) {
    int numInserts = DeepState_IntInRange(1, 20);  // Inserts 1 to 20 elements
    for (int i = 0; i < numInserts; i++) {
        int val = DeepState_Int();
        LOG(INFO) << "Inserting value: " << val;
        tree.insert(val);
        ASSERT(tree.validateRBProperties()) << "Red-Black property violated after insertion!";
    }
}

void randomDeleteTest(RedBlackTree& tree) {
    int numDeletes = DeepState_IntInRange(1, 10);  // Deletes 1 to 10 elements
    for (int i = 0; i < numDeletes; i++) {
        int val = DeepState_Int();
        LOG(INFO) << "Deleting value: " << val;
        tree.deleteNode(val);
        ASSERT(tree.validateRBProperties()) << "Red-Black property violated after deletion!";
    }
}

TEST(RedBlackTree, RandomInserts) {
    RedBlackTree tree;
    randomInsertTest(tree);
}

TEST(RedBlackTree, InsertThenDelete) {
    RedBlackTree tree;
    randomInsertTest(tree);
    randomDeleteTest(tree);
}
