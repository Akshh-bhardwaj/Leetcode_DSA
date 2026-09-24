// 474. Ones and Zeroes — C (Bottom-up 2D DP)
#include <stdlib.h>
#include <string.h>

static void count01(const char *s, int *zeros, int *ones) {
    int z = 0, o = 0;
    for (const char *p = s; *p; ++p) {
        if (*p == '0') ++z;
        else if (*p == '1') ++o;
    }
    *zeros = z; *ones = o;
}

int findMaxForm(char **strs, int strsSize, int m, int n) {
    // dp[i][j] = max number of strings using at most i zeros and j ones
    int rows = m + 1, cols = n + 1;
    int *dp = (int *)calloc(rows * cols, sizeof(int));
    if (!dp) return 0;

    for (int s = 0; s < strsSize; ++s) {
        int z = 0, o = 0;
        count01(strs[s], &z, &o);

        // Reverse iterate to ensure 0/1 knapsack (use each string at most once)
        for (int i = m; i >= z; --i) {
            for (int j = n; j >= o; --j) {
                int idx = i * cols + j;
                int prevIdx = (i - z) * cols + (j - o);
                int candidate = dp[prevIdx] + 1;
                if (candidate > dp[idx]) dp[idx] = candidate;
            }
        }
    }

    int ans = dp[m * cols + n];
    free(dp);
    return ans;
}
