#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* finalPrices(int* prices, int pricesSize, int* returnSize) {
    *returnSize = pricesSize;

    int* ans = (int*)malloc(pricesSize * sizeof(int));
    int stack[pricesSize];
    int top = -1;

    for (int i = 0; i < pricesSize; i++) {
        ans[i] = prices[i];
    }

    for (int i = 0; i < pricesSize; i++) {
        while (top != -1 && prices[stack[top]] >= prices[i]) {
            ans[stack[top]] -= prices[i];
            top--;
        }
        stack[++top] = i;
    }

    return ans;
}
