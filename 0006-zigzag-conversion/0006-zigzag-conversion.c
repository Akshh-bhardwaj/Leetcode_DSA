char* convert(char* s, int numRows) {
    int len = strlen(s);
    if (numRows == 1 || numRows >= len)
        return strdup(s);

    char** rows = (char**)malloc(numRows * sizeof(char*));
    int* pos = (int*)calloc(numRows, sizeof(int));
    for (int i = 0; i < numRows; i++)
        rows[i] = (char*)calloc(len + 1, sizeof(char));

    int currRow = 0;
    int goingDown = 0;

    for (int i = 0; i < len; i++) {
        rows[currRow][pos[currRow]++] = s[i];
        if (currRow == 0 || currRow == numRows - 1)
            goingDown = !goingDown;
        currRow += goingDown ? 1 : -1;
    }

    char* result = (char*)malloc((len + 1) * sizeof(char));
    int k = 0;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < pos[i]; j++) {
            result[k++] = rows[i][j];
        }
        free(rows[i]);
    }
    result[k] = '\0';

    free(rows);
    free(pos);
    return result;
}
