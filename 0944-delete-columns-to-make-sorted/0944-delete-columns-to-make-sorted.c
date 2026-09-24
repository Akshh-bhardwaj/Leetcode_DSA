int minDeletionSize(char **strs, int strsSize) {
    int i, j;
    int deleteCount = 0;

    if (strsSize <= 1) return 0;

    int m = strlen(strs[0]); // number of columns

    for (j = 0; j < m; j++) {
        for (i = 1; i < strsSize; i++) {
            if (strs[i][j] < strs[i - 1][j]) {
                deleteCount++;
                break; // go to next column
            }
        }
    }

    return deleteCount;
}
