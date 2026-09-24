void rotate(int** mat, int rs, int* cs) {
    int n = rs;
    for (int i = 0; i < n >> 1; i++) {
        for (int j = i; j < n - 1 - i; j++) {
            int t = mat[i][j];
            mat[i][j] = mat[~j + n][i];
            mat[~j + n][i] = mat[~i + n][~j + n];
            mat[~i + n][~j + n] = mat[j][~i + n];
            mat[j][~i + n] = t;
        }
    }
}