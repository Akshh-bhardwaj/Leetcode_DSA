/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

static long long totalSum;
static long long bestProduct;

// helper to compute subtree sums and update best product
long long dfs(struct TreeNode* node) {
    if (node == NULL) return 0;
    long long leftSum = dfs(node->left);
    long long rightSum = dfs(node->right);
    long long subtreeSum = leftSum + rightSum + node->val;
    long long other = totalSum - subtreeSum;
    // update best product
    if (other * subtreeSum > bestProduct) {
        bestProduct = other * subtreeSum;
    }
    return subtreeSum;
}

int maxProduct(struct TreeNode* root) {
    const long long MOD = 1000000007LL;
    // first compute total sum of all nodes
    totalSum = dfs(root);
    bestProduct = 0;
    // second pass to compute best split
    dfs(root);
    return (int)(bestProduct % MOD);
}
