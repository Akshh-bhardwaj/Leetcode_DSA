int** constructProductMatrix(int** grid, int gridSize, int* gridColSize,
                             int* returnSize, int** returnColumnSizes) {
    const int MOD = 12345;
    int n = gridSize, m = gridColSize[0];

    int** p = (int**)malloc(n * sizeof(int*));
    *returnColumnSizes = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        p[i] = (int*)malloc(m * sizeof(int));
        (*returnColumnSizes)[i] = m;
    }
    *returnSize = n;

    long long suffix = 1;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            p[i][j] = suffix % MOD;
            suffix = (suffix * grid[i][j]) % MOD;
        }
    }

    long long prefix = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            p[i][j] = (p[i][j] * prefix) % MOD;
            prefix = (prefix * grid[i][j]) % MOD;
        }
    }

    return p;
}