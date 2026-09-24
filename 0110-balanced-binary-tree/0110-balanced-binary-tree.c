/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int checkHeight(struct TreeNode* root) {
    if (root == NULL)
        return 0;

    int leftH = checkHeight(root->left);
    if (leftH == -1) return -1; // left subtree unbalanced

    int rightH = checkHeight(root->right);
    if (rightH == -1) return -1; // right subtree unbalanced

    if (abs(leftH - rightH) > 1) 
        return -1; // this node is unbalanced

    return (leftH > rightH ? leftH : rightH) + 1;
}

bool isBalanced(struct TreeNode* root){
    return checkHeight(root) != -1;
}
