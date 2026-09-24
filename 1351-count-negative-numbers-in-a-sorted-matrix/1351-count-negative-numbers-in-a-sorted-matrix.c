int countNegatives(int** grid, int gridSize, int* gridColSize){
    int m = gridSize;
    int n = gridColSize[0];
    int count = 0;

    // Start from bottom-left
    int i = m - 1, j = 0;

    while (i >= 0 && j < n) {
        if (grid[i][j] < 0) {
            // grid[i][j] < 0, so all from j to n-1 are negative
            count += (n - j);
            i--;  // move up
        } else {
            j++;  // move right
        }
    }

    return count;
}
