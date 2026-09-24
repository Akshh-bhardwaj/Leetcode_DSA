/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int maxLevelSum(struct TreeNode* root){
    if (root == NULL) return 0;
    
    // Use a queue for BFS
    struct TreeNode* queue[10000];
    int front = 0, back = 0;
    
    // Enqueue root
    queue[back++] = root;
    
    int maxSum = INT_MIN;
    int resultLevel = 1;
    int currentLevel = 1;
    
    while (front < back) {
        int levelSize = back - front;
        long long levelSum = 0;
        
        // Process all nodes at current level
        for (int i = 0; i < levelSize; ++i) {
            struct TreeNode* node = queue[front++];
            levelSum += node->val;
            
            if (node->left) {
                queue[back++] = node->left;
            }
            if (node->right) {
                queue[back++] = node->right;
            }
        }
        
        // Update max sum and result if this level is larger
        if (levelSum > maxSum) {
            maxSum = levelSum;
            resultLevel = currentLevel;
        }
        
        ++currentLevel;
    }
    
    return resultLevel;
}
