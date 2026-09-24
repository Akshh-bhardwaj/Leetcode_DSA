bool areSimilar(int** mat, int n, int* matColSize, int k) {
    int m = *matColSize;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] != mat[i][((j - k) % m + m) % m]) {
                    return false;
                }
            }
        } else {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] != mat[i][(j + k) % m]) {
                    return false;
                }
            }
        }
    }
    return true;
}