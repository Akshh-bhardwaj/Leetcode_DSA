#include <stdbool.h>

bool isMagic(int** grid, int r, int c) {
    bool seen[10] = {false};

    // Check numbers 1 to 9 and uniqueness
    for (int i = r; i < r + 3; i++) {
        for (int j = c; j < c + 3; j++) {
            int val = grid[i][j];
            if (val < 1 || val > 9 || seen[val])
                return false;
            seen[val] = true;
        }
    }

    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        int rowSum = 0, colSum = 0;
        for (int j = 0; j < 3; j++) {
            rowSum += grid[r + i][c + j];
            colSum += grid[r + j][c + i];
        }
        if (rowSum != 15 || colSum != 15)
            return false;
    }

    // Check diagonals
    if (grid[r][c] + grid[r+1][c+1] + grid[r+2][c+2] != 15)
        return false;
    if (grid[r][c+2] + grid[r+1][c+1] + grid[r+2][c] != 15)
        return false;

    return true;
}

int numMagicSquaresInside(int** grid, int gridSize, int* gridColSize) {
    if (gridSize < 3 || gridColSize[0] < 3)
        return 0;

    int count = 0;

    for (int i = 0; i <= gridSize - 3; i++) {
        for (int j = 0; j <= gridColSize[0] - 3; j++) {
            if (isMagic(grid, i, j))
                count++;
        }
    }
    return count;
}
