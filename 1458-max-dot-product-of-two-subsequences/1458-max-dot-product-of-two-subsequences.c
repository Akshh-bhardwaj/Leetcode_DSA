#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int maxDotProduct(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int n = nums1Size, m = nums2Size;
    
    // dp[i][j] = max dot product using nums1[0..i] and nums2[0..j]
    int **dp = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        dp[i] = (int *)malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            dp[i][j] = INT_MIN;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int prod = nums1[i] * nums2[j];

            // take current pair alone or extend previous subsequence
            int take = prod;
            if (i > 0 && j > 0 && dp[i-1][j-1] > 0) {
                take += dp[i-1][j-1];
            }

            int skip1 = (i > 0) ? dp[i-1][j] : INT_MIN;
            int skip2 = (j > 0) ? dp[i][j-1] : INT_MIN;

            dp[i][j] = max(take, max(skip1, skip2));
        }
    }

    int result = dp[n-1][m-1];

    // free memory
    for (int i = 0; i < n; i++) free(dp[i]);
    free(dp);

    return result;
}
