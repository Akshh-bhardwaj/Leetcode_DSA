#include <stdlib.h>

// Function to perform diagonal traversal
int* findDiagonalOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    if (matrixSize == 0 || matrixColSize[0] == 0) {
        *returnSize = 0;
        return NULL;
    }

    int m = matrixSize;
    int n = matrixColSize[0];
    int total = m * n;
    int* result = (int*)malloc(total * sizeof(int));
    int idx = 0;

    // Direction flag: 1 = up-right, -1 = down-left
    int dir = 1;  
    int r = 0, c = 0;

    while (idx < total) {
        result[idx++] = matrix[r][c];

        // Move in current diagonal direction
        r -= dir;
        c += dir;

        // Boundary adjustments
        if (r == m) {         // Went down past last row
            r = m - 1;
            c += 2;
            dir = -dir;
        }
        if (c == n) {         // Went right past last column
            c = n - 1;
            r += 2;
            dir = -dir;
        }
        if (r < 0) {          // Went up past first row
            r = 0;
            dir = -dir;
        }
        if (c < 0) {          // Went left past first column
            c = 0;
            dir = -dir;
        }
    }

    *returnSize = total;
    return result;
}
