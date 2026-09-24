bool canPartitionGrid(int** grid, int gridSize, int* gridColSize) {
    long long total = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[0]; j++) {
            total += grid[i][j];
        }
    }

    if (total & 1)
        return false;

    // calculate row wise running sum
    long long curr = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[0]; j++) {
            curr += grid[i][j];
        }
        if (curr == total / 2)
            return true;
        if (curr > total / 2)
            break;
    }

    curr = 0;
    // calculate col wise running sum
    for (int i = 0; i < gridColSize[0]; i++) {
        for (int j = 0; j < gridSize; j++) {
            curr += grid[j][i];
        }
        if (curr == total / 2)
            return true;
        if (curr > total / 2)
            break;
    }

    return false;
}