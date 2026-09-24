/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct Result {
    struct TreeNode* node;
    int depth;
};

struct Result dfs(struct TreeNode* root) {
    if (!root) {
        struct Result r = {NULL, 0};
        return r;
    }
    struct Result left = dfs(root->left);
    struct Result right = dfs(root->right);

    // if left and right depths are same, root is LCA of deepest
    if (left.depth == right.depth) {
        struct Result r = {root, left.depth + 1};
        return r;
    }
    // if left is deeper, propagate left
    if (left.depth > right.depth) {
        struct Result r = {left.node, left.depth + 1};
        return r;
    }
    // right is deeper
    struct Result r = {right.node, right.depth + 1};
    return r;
}

struct TreeNode* subtreeWithAllDeepest(struct TreeNode* root) {
    return dfs(root).node;
}
