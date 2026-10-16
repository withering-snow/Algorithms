#include "../avl.hpp"

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
    deleteNode(root);
}


void AVL::insert(int val) {
    root = insertNode(root, val);
}


void AVL::remove(int val) {
    root = removeNode(root, val);
}

int AVL::rank(int val) {
    TreeNode *node = root;
    int smaller = 0;
    while (node != nullptr) {
        if (val < node->val) {
            node = node->left;
        } else if (val > node->val) {
            smaller += getSize(node->left) + node->count;
            node = node->right;
        } else { // val == node->val
            return smaller + getSize(node->left) + 1;
        }
    }
    return smaller + 1;
}

int AVL::kth(int k) {
    if (k <= 0 || k > getSize(root))
        return -1;
    TreeNode* node = root;
    while (node != nullptr) {
        int leftSize = getSize(node->left);
        if (k <= leftSize) {
            node = node->left;
        } else if (k <= leftSize + node->count) {
            return node->val;
        } else { // k > leftSize + node->count
            k -= leftSize + node->count;
            node = node->right;
        }
    }
    return -1;
}

int AVL::prev(int val) {
    int result = INT_MIN;
    TreeNode *node = root;
    while (node != nullptr) {
        if (val <= node->val) {
            node = node->left;
        } else { // val > node->val
            result = node->val;
            node = node->right;
        }
    }
    return result;
}

int AVL::next(int val) {
    int result = INT_MAX;
    TreeNode *node = root;
    while (node != nullptr) {
        if (val >= node->val) {
            node = node->right;
        } else { // val < node->val
            result = node->val;
            node = node->left;
        }
    }
    return result;
}


int AVL::getHeight(TreeNode *node) {
    if (node == nullptr) return 0;
    return node->height;
}

int AVL::getSize(TreeNode *node) {
    if (node == nullptr) return 0;
    return node->size;
}

int AVL::getBalance(TreeNode *node) {
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void AVL::updateInfo(TreeNode *node) {
    if (node == nullptr) return;
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    node->size = getSize(node->left) + getSize(node->right) + node->count;
}

AVL::TreeNode * AVL::minNode(TreeNode* node) {
    if (node == nullptr)
        return nullptr;
    while (node->left != nullptr)
        node = node->left;
    return node;
}

AVL::TreeNode * AVL::maxNode(TreeNode* node) {
    if (node == nullptr)
        return nullptr;
    while (node->right != nullptr)
        node = node->right;
    return node;
}

AVL::TreeNode * AVL::rotateLeft(TreeNode *node) {
    TreeNode *root = node->right;
    node->right = root->left;
    root->left = node;
    updateInfo(node);
    updateInfo(root);
    return root;
}

AVL::TreeNode * AVL::rotateRight(TreeNode *node) {
    TreeNode *root = node->left;
    node->left = root->right;
    root->right = node;
    updateInfo(node);
    updateInfo(root);
    return root;
}

AVL::TreeNode* AVL::rebalance(TreeNode* root) {
    if (root == nullptr)
        return nullptr;
    updateInfo(root);
    int balance = getBalance(root);
    // 左边太高
    if (balance > 1) {
        // LR
        if (getBalance(root->left) < 0)
            root->left = rotateLeft(root->left);
        // LL
        return rotateRight(root);
    }
    // 右边太高
    if (balance < -1) {
        // RL
        if (getBalance(root->right) > 0)
            root->right = rotateRight(root->right);
        // RR
        return rotateLeft(root);
    }
    return root;
}

AVL::TreeNode * AVL::insertNode(TreeNode *node, int val) {
    if (node == nullptr) {
        return new TreeNode(val);
    }
    if (val > node->val) {
        node->right = insertNode(node->right, val);
    } else if (val < node->val) {
        node->left = insertNode(node->left, val);
    } else { // val == node->val
        ++(node->count);
    }
    return rebalance(node);
}

AVL::TreeNode * AVL::removeNode(TreeNode *node, int val) {
    if (node == nullptr) {
        return node;
    }
    if (val > node->val) {
        node->right = removeNode(node->right, val);
    } else if (val < node->val) {
        node->left = removeNode(node->left, val);
    } else { // val == node->val
        if (node->count > 1) {
            --(node->count);
        } else { // node->count == 1
            if (node->left == nullptr) {
                TreeNode *right = node->right;
                delete node;
                return right;
            } else if (node->right == nullptr) {
                TreeNode *left = node->left;
                delete node;
                return left;
            } else { // node->left != nullptr && node->right != nullptr
                TreeNode* target = minNode(node->right);
                node->val = target->val;
                node->count = target->count;
                target->count = 1;
                node->right = removeNode(node->right, target->val);
            }
        }
    }
    return rebalance(node);
}

void AVL::deleteNode(TreeNode *node) {
    if (node == nullptr) {
        return;
    }
    deleteNode(node->left);
    deleteNode(node->right);
    delete node;
}