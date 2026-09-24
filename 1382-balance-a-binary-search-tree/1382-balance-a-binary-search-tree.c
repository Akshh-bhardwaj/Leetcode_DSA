/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void inorderTraversal(struct TreeNode* root, int* arr, int* sz) {
    if (root == NULL) return;
    inorderTraversal(root->left, arr, sz);
    arr[(*sz)++] = root->val;
    inorderTraversal(root->right, arr, sz);
}

struct TreeNode* buildBalanced(int* arr, int start, int end) {
    if (start > end) return NULL;
    int mid = (start + end) / 2;

    struct TreeNode* node = malloc(sizeof(struct TreeNode));
    node->val = arr[mid];

    node->left = buildBalanced(arr, start, mid - 1);
    node->right = buildBalanced(arr, mid + 1, end);

    return node;
}

struct TreeNode* balanceBST(struct TreeNode* root) {
    if (root == NULL) return NULL;

    int arr[10000]; // large enough for typical constraints
    int sz = 0;

    inorderTraversal(root, arr, &sz);

    return buildBalanced(arr, 0, sz - 1);
}
