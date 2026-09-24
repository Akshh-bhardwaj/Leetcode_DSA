#include <stdlib.h>

// gcd function
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* replaceNonCoprimes(int* nums, int numsSize, int* returnSize) {
    int* stack = (int*)malloc(sizeof(int) * numsSize);
    int top = -1;
    
    for (int i = 0; i < numsSize; i++) {
        int cur = nums[i];
        
        // Merge with stack top if not coprime
        while (top >= 0) {
            int g = gcd(stack[top], cur);
            if (g == 1) break;
            cur = (stack[top] / g) * cur; // lcm = a/gcd * b
            top--;
        }
        
        stack[++top] = cur;
    }
    
    *returnSize = top + 1;
    return stack;
}
