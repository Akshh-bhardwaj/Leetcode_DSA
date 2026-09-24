#include <stdlib.h>
#include <limits.h>

/*
 LeetCode 120 - Triangle
 Signature expected by LeetCode:
   int minimumTotal(int** triangle, int triangleSize, int* triangleColSize);
*/
int minimumTotal(int** triangle, int triangleSize, int* triangleColSize) {
    if (triangleSize == 0) return 0;

    // dp[i] will hold the min path sum to reach position i in current row
    int *dp = (int*)malloc(sizeof(int) * triangleSize);
    if (!dp) return 0; // allocation fail guard (LeetCode won't normally hit this)

    // initialize dp with large values
    for (int i = 0; i < triangleSize; ++i) dp[i] = INT_MAX;

    dp[0] = triangle[0][0];

    // process rows from 1..triangleSize-1
    for (int r = 1; r < triangleSize; ++r) {
        int cols = triangleColSize[r]; // should equal r+1
        // update from right to left so we don't overwrite needed previous-row values
        for (int c = cols - 1; c >= 0; --c) {
            int val = triangle[r][c];
            if (c == 0) {
                // only can come from previous dp[0]
                dp[c] = dp[c] + val;
            } else if (c == cols - 1) {
                // rightmost element, only from previous dp[c-1]
                dp[c] = dp[c - 1] + val;
            } else {
                // choose min of dp[c-1] and dp[c] (both from previous row)
                int left = dp[c - 1];
                int up = dp[c];
                dp[c] = (left < up ? left : up) + val;
            }
        }
    }

    // answer is min value in last row (dp[0..triangleSize-1])
    int ans = INT_MAX;
    for (int i = 0; i < triangleSize; ++i)
        if (dp[i] < ans) ans = dp[i];

    free(dp);
    return ans;
}
