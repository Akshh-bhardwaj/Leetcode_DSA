#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int minDeletionSize(char **strs, int strsSize) {
    if (strsSize <= 1) return 0;

    int n = strsSize;
    int m = strlen(strs[0]);

    bool *sortedPairs = (bool *)calloc(n - 1, sizeof(bool));
    int deletions = 0;

    for (int col = 0; col < m; col++) {
        bool deleteCol = false;

        // Check violation
        for (int i = 0; i < n - 1; i++) {
            if (!sortedPairs[i] && strs[i][col] > strs[i + 1][col]) {
                deleteCol = true;
                break;
            }
        }

        if (deleteCol) {
            deletions++;
            continue;
        }

        // Mark sorted pairs
        for (int i = 0; i < n - 1; i++) {
            if (!sortedPairs[i] && strs[i][col] < strs[i + 1][col]) {
                sortedPairs[i] = true;
            }
        }
    }

    free(sortedPairs);
    return deletions;
}
