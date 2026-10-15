#pragma once

class AVL {
public:
    AVL() = default;
    ~AVL();

    AVL(const AVL&) = delete;
    AVL& operator=(const AVL&) = delete;

    void insert(int val);
    void remove(int val);

    int rank(int val);
    int kth(int k);
    int prev(int val);
    int next(int val);

private:
    friend struct AVLInspector;
    struct TreeNode {
        TreeNode* left;
        TreeNode* right;
        int val;

        int count;
        int height;
        int size;

        TreeNode(int val);
    };

    TreeNode* root = nullptr;

    static int getHeight(TreeNode* node);
    static int getSize(TreeNode* node);
    static int getBalance(TreeNode* node);

    static void updateInfo(TreeNode* node);

    static TreeNode* minNode(TreeNode* node);
    static TreeNode* maxNode(TreeNode* node);

    static TreeNode* rotateLeft(TreeNode* node);
    static TreeNode* rotateRight(TreeNode* node);
    static TreeNode* rebalance(TreeNode* node);

    static TreeNode* insertNode(TreeNode* node, int val);
    static TreeNode* removeNode(TreeNode* node, int val);

    static void deleteNode(TreeNode* node);
};