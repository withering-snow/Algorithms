#include "avl.hpp"

#include <algorithm>
#include <climits>


AVL::TreeNode::TreeNode(int val)
    : left(nullptr),
      right(nullptr),
      val(val),
      count(1),
      height(1),
      size(1) {}


AVL::~AVL() {

}


void AVL::insert(int val) {

}


void AVL::remove(int val) {

}


int AVL::rank(int val) {

}


int AVL::kth(int k) {

}


int AVL::prev(int val) {

}


int AVL::next(int val) {

}


int AVL::getHeight(TreeNode* node) {

}


int AVL::getSize(TreeNode* node) {

}


int AVL::getBalance(TreeNode* node) {

}


void AVL::updateInfo(TreeNode* node) {

}


AVL::TreeNode* AVL::minNode(TreeNode* node) {

}


AVL::TreeNode* AVL::maxNode(TreeNode* node) {

}


AVL::TreeNode* AVL::rotateLeft(TreeNode* node) {

}


AVL::TreeNode* AVL::rotateRight(TreeNode* node) {

}


AVL::TreeNode* AVL::rebalance(TreeNode* node) {

}


AVL::TreeNode* AVL::insertNode(TreeNode* node, int val) {

}


AVL::TreeNode* AVL::removeNode(TreeNode* node, int val) {

}


void AVL::deleteNode(TreeNode* node) {

}