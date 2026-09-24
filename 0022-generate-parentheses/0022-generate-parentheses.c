#include <stdlib.h>
#include <string.h>

// helper to append a result string, resizing as needed
static void add_result(char ***res, int *size, int *cap, const char *s) {
    if (*size >= *cap) {
        *cap = (*cap == 0) ? 8 : (*cap * 2);
        *res = realloc(*res, (*cap) * sizeof(char*));
    }
    (*res)[(*size)++] = strdup(s);
}

// backtracking recursion
static void backtrack(char ***res, int *size, int *cap, char *buffer, int pos, int open, int close, int n) {
    if (pos == 2 * n) {
        buffer[pos] = '\0';
        add_result(res, size, cap, buffer);
        return;
    }
    if (open < n) {
        buffer[pos] = '(';
        backtrack(res, size, cap, buffer, pos + 1, open + 1, close, n);
    }
    if (close < open) {
        buffer[pos] = ')';
        backtrack(res, size, cap, buffer, pos + 1, open, close + 1, n);
    }
}

char ** generateParenthesis(int n, int* returnSize){
    char **results = NULL;
    int size = 0, cap = 0;

    if (n == 0) {
        // edge case: return [""]
        results = malloc(sizeof(char*));
        results[0] = strdup("");
        *returnSize = 1;
        return results;
    }

    char *buffer = malloc((2 * n + 1) * sizeof(char));
    backtrack(&results, &size, &cap, buffer, 0, 0, 0, n);
    free(buffer);
    *returnSize = size;
    return results;
}
