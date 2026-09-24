#include <stdlib.h>

int maxSideLength(int** mat, int matSize, int* matColSize, int threshold){
    int m = matSize;
    int n = matColSize[0];

    // allocate prefix sum with 1 extra row and col
    int** prefix = (int**)malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        prefix[i] = (int*)malloc((n + 1) * sizeof(int));
        for (int j = 0; j <= n; j++) {
            prefix[i][j] = 0;
        }
    }

    // build 2D prefix sum
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            prefix[i][j] = prefix[i - 1][j] 
                         + prefix[i][j - 1] 
                         - prefix[i - 1][j - 1] 
                         + mat[i - 1][j - 1];
        }
    }

    // check if any k x k square has sum <= threshold
    int check = 0;
    int l = 0, r = (m < n ? m : n);

    while (l < r) {
        int mid = (l + r + 1) >> 1;
        int found = 0;
        for (int i = 0; i + mid <= m && !found; i++) {
            for (int j = 0; j + mid <= n; j++) {
                int sum = prefix[i + mid][j + mid]
                        - prefix[i][j + mid]
                        - prefix[i + mid][j]
                        + prefix[i][j];
                if (sum <= threshold) {
                    found = 1;
                    break;
                }
            }
        }
        if (found) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }

    // free memory
    for (int i = 0; i <= m; i++) {
        free(prefix[i]);
    }
    free(prefix);

    return l;
}
