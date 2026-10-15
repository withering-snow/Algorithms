#include "avl.hpp"

#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <random>

struct AVLInspector {
public:
    static void check(const AVL &tree) {
        checkNode(tree.root, LLONG_MIN, LLONG_MAX);
    }
private:
    struct Info {
        int height;
        int size;
    };
    static Info checkNode( 
        AVL::TreeNode* node,
        long long low, long long high
    ) {
        if (node == nullptr)
            return {0, 0};

        // 1. 检查当前节点 BST 范围
        assert(node->val > low && node->val < high);
        // 2. 递归检查左右子树
        Info left = checkNode(node->left, low, node->val);
        Info right = checkNode(node->right, node->val, high);

        // 3. 自己重新计算 height / size
        Info current = {
            std::max(left.height, right.height) + 1, 
            left.size + right.size + node->count
        };

        // 4. assert:
        //    balance
        assert(std::abs(left.height - right.height) <= 1);
        //    stored height
        assert(node->height == current.height);
        //    stored size
        assert(node->size == current.size);
        //    count
        assert(node->count > 0);

        // 5. return 当前真实信息
        return current;
    }
};

void testInsertLL() {
    AVL tree;

    tree.insert(30);
    tree.insert(20);
    tree.insert(10);

    assert(tree.kth(1) == 10);
    assert(tree.kth(2) == 20);
    assert(tree.kth(3) == 30);

    assert(tree.rank(20) == 2);
    assert(tree.prev(20) == 10);
    assert(tree.next(20) == 30);

    AVLInspector::check(tree);
}

void testInsertRR() {
    AVL tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);

    assert(tree.kth(1) == 10);
    assert(tree.kth(2) == 20);
    assert(tree.kth(3) == 30);

    assert(tree.rank(20) == 2);
    assert(tree.prev(20) == 10);
    assert(tree.next(20) == 30);

    AVLInspector::check(tree);
}

void testInsertLR() {
    AVL tree;

    tree.insert(30);
    tree.insert(10);
    tree.insert(20);

    assert(tree.kth(1) == 10);
    assert(tree.kth(2) == 20);
    assert(tree.kth(3) == 30);

    assert(tree.rank(20) == 2);
    assert(tree.prev(20) == 10);
    assert(tree.next(20) == 30);

    AVLInspector::check(tree);
}

void testInsertRL() {
    AVL tree;

    tree.insert(10);
    tree.insert(30);
    tree.insert(20);

    assert(tree.kth(1) == 10);
    assert(tree.kth(2) == 20);
    assert(tree.kth(3) == 30);

    assert(tree.rank(20) == 2);
    assert(tree.prev(20) == 10);
    assert(tree.next(20) == 30);

    AVLInspector::check(tree);
}

void testInsertDuplicate() {
    AVL tree;

    tree.insert(20);
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(20);

    assert(tree.kth(1) == 10);
    assert(tree.kth(2) == 20);
    assert(tree.kth(3) == 20);
    assert(tree.kth(4) == 20);
    assert(tree.kth(5) == 30);

    assert(tree.rank(10) == 1);
    assert(tree.rank(20) == 2);
    assert(tree.rank(30) == 5);

    assert(tree.prev(20) == 10);
    assert(tree.next(20) == 30);

    AVLInspector::check(tree);
}

void testRemoveDuplicate() {
    AVL tree;

    tree.insert(20);
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(20);

    tree.remove(20);

    assert(tree.kth(2) == 20);
    assert(tree.kth(3) == 20);
    assert(tree.kth(4) == 30);
    assert(tree.kth(5) == -1);
    assert(tree.rank(20) == 2);
    assert(tree.rank(30) == 4);

    AVLInspector::check(tree);

    tree.remove(20);

    assert(tree.kth(2) == 20);
    assert(tree.kth(3) == 30);
    assert(tree.kth(4) == -1);
    assert(tree.rank(20) == 2);
    assert(tree.rank(30) == 3);

    AVLInspector::check(tree);
}

void testRemoveLeaf() {
    AVL tree;

    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    
    tree.remove(10);

    assert(tree.kth(1) == 20);
    assert(tree.kth(2) == 30);
    assert(tree.rank(20) == 1);
    assert(tree.rank(30) == 2);
    assert(tree.rank(10) == 1);

    AVLInspector::check(tree);
}

void testRemoveOneChild() {
    AVL tree;
    
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(40);

    tree.remove(30);
    
    assert(tree.kth(1) == 10);
    assert(tree.kth(2) == 20);
    assert(tree.kth(3) == 40);

    assert(tree.rank(10) == 1);
    assert(tree.rank(20) == 2);
    assert(tree.rank(30) == 3);
    assert(tree.rank(40) == 3);

    AVLInspector::check(tree);

    tree.insert(30);

    tree.remove(40);

    assert(tree.kth(1) == 10);
    assert(tree.kth(2) == 20);
    assert(tree.kth(3) == 30);

    assert(tree.rank(10) == 1);
    assert(tree.rank(20) == 2);
    assert(tree.rank(30) == 3);

    AVLInspector::check(tree);
}

void testRemoveTwoChildren() {
    for (int round = 0; round < 2; ++round) {
        AVL tree;

        tree.insert(20);
        tree.insert(10);
        tree.insert(30);
        tree.insert(15);
        tree.insert(15);
        tree.insert(25);
        tree.insert(25);

        tree.remove(20);

        assert(tree.kth(1) == 10);
        assert(tree.kth(2) == 15);
        assert(tree.kth(3) == 15);
        assert(tree.kth(4) == 25);
        assert(tree.kth(5) == 25);
        assert(tree.kth(6) == 30);

        assert(tree.rank(10) == 1);
        assert(tree.rank(15) == 2);
        assert(tree.rank(20) == 4);
        assert(tree.rank(25) == 4);
        assert(tree.rank(30) == 6);

        AVLInspector::check(tree);
    }
}

void testRemoveNone() {
    AVL tree;

    tree.insert(20);
    tree.insert(10);
    tree.insert(30);

    tree.remove(5);
    tree.remove(15);
    tree.remove(25);
    tree.remove(35);

    assert(tree.kth(1) == 10);
    assert(tree.kth(2) == 20);
    assert(tree.kth(3) == 30);

    assert(tree.rank(20) == 2);
    assert(tree.prev(20) == 10);
    assert(tree.next(20) == 30);

    AVLInspector::check(tree);
}

void testRemoveCascadeRebalance() {
    AVL tree;

    tree.insert(7);
    tree.insert(3);
    tree.insert(5);
    tree.insert(8);
    tree.insert(4);
    tree.insert(11);
    tree.insert(9);
    tree.insert(6);
    tree.insert(2);
    tree.insert(12);
    tree.insert(1);
    tree.insert(10);

    AVLInspector::check(tree);

    tree.remove(4);

    assert(tree.kth(3) == 3);
    assert(tree.kth(4) == 5);
    assert(tree.rank(4) == 4);
    assert(tree.rank(5) == 4);

    AVLInspector::check(tree);
}

void testRank() {
    AVL tree;

    assert(tree.rank(123) == 1);

    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(20);

    assert(tree.rank(5) == 1);
    assert(tree.rank(10) == 1);
    assert(tree.rank(20) == 2);
    assert(tree.rank(15) == 2);
    assert(tree.rank(30) == 4);
    assert(tree.rank(40) == 5);
}

void testKth() {
    AVL tree;

    assert(tree.kth(1) == -1);

    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(20);

    assert(tree.kth(0) == -1);
    assert(tree.kth(-1) == -1);

    assert(tree.kth(1) == 10);
    assert(tree.kth(2) == 20);
    assert(tree.kth(3) == 20);
    assert(tree.kth(4) == 30);

    assert(tree.kth(5) == -1);
}

void testPrev() {
    AVL tree;

    assert(tree.prev(123) == INT_MIN);

    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(20);

    assert(tree.prev(5) == INT_MIN);
    assert(tree.prev(10) == INT_MIN);

    assert(tree.prev(15) == 10);
    assert(tree.prev(20) == 10);
    assert(tree.prev(21) == 20);
    assert(tree.prev(30) == 20);
    assert(tree.prev(40) == 30);
}

void testNext() {
    AVL tree;

    assert(tree.next(123) == INT_MAX);

    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(20);

    assert(tree.next(5) == 10);
    assert(tree.next(10) == 20);
    assert(tree.next(15) == 20);
    assert(tree.next(20) == 30);
    assert(tree.next(30) == INT_MAX);
    assert(tree.next(40) == INT_MAX);
}

void testRandomInsertRemove() {
    AVL tree;

    std::mt19937 rng(12345);
    std::uniform_int_distribution<int> opDist(0, 1);
    std::uniform_int_distribution<int> valueDist(-50, 50);

    for (int step = 0; step < 1000; ++step) {
        int op = opDist(rng);
        int val = valueDist(rng);
        if (op == 0) {
            tree.insert(val);
        } else {
            tree.remove(val);
        }
        AVLInspector::check(tree);
    }
}

int main() {
    testInsertLL();

    std::cout << "All tests passed.\n";
    return 0;
}