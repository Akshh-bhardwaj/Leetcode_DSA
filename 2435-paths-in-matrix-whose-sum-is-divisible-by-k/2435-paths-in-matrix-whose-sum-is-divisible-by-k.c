#include <stdlib.h>

#define MOD 1000000007

int numberOfPaths(int** grid, int gridSize, int* gridColSize, int k) {
    int m = gridSize;
    int n = gridColSize[0];

    // dp[i][j][r] = number of ways to reach cell (i,j) with sum % k = r
    int*** dp = (int***)malloc(m * sizeof(int**));
    for (int i = 0; i < m; i++) {
        dp[i] = (int**)malloc(n * sizeof(int*));
        for (int j = 0; j < n; j++) {
            dp[i][j] = (int*)calloc(k, sizeof(int));
        }
    }

    int r0 = grid[0][0] % k;
    dp[0][0][r0] = 1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int val = grid[i][j];

            for (int r = 0; r < k; r++) {
                int ways = dp[i][j][r];
                if (ways == 0) continue;

                // Move down
                if (i + 1 < m) {
                    int nr = (r + grid[i + 1][j]) % k;
                    dp[i + 1][j][nr] = (dp[i + 1][j][nr] + ways) % MOD;
                }

                // Move right
                if (j + 1 < n) {
                    int nr = (r + grid[i][j + 1]) % k;
                    dp[i][j + 1][nr] = (dp[i][j + 1][nr] + ways) % MOD;
                }
            }
        }
    }

    int ans = dp[m-1][n-1][0];

    // free memory
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            free(dp[i][j]);
        free(dp[i]);
    }
    free(dp);

    return ans;
}
