int minDeletionSize(char **strs, int strsSize) {
    int n = strsSize;
    int m = strlen(strs[0]);

    int dp[m];
    for (int i = 0; i < m; i++) {
        dp[i] = 1;
    }

    for (int j = 0; j < m; j++) {
        for (int i = 0; i < j; i++) {
            int valid = 1;
            for (int r = 0; r < n; r++) {
                if (strs[r][i] > strs[r][j]) {
                    valid = 0;
                    break;
                }
            }
            if (valid) {
                dp[j] = dp[j] > dp[i] + 1 ? dp[j] : dp[i] + 1;
            }
        }
    }

    int maxKeep = 0;
    for (int i = 0; i < m; i++) {
        if (dp[i] > maxKeep)
            maxKeep = dp[i];
    }

    return m - maxKeep;
}

