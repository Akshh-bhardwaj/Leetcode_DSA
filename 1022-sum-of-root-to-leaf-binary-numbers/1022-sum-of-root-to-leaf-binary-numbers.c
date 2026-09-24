int dfs(struct TreeNode* root, int val){
    if(!root) return 0;

    val = (val << 1) | root->val;

    if(!root->left && !root->right)
        return val;

    return dfs(root->left, val) + dfs(root->right, val);
}

int sumRootToLeaf(struct TreeNode* root){
    return dfs(root, 0);
}