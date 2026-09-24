long long maxMatrixSum(int** matrix, int matrixSize, int* matrixColSize) {
    long long totalSum = 0;
    int negCount = 0;
    int minAbs = 2147483647; // INT_MAX

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixColSize[i]; j++) {
            int val = matrix[i][j];

            if (val < 0)
                negCount++;

            int absVal = val < 0 ? -val : val;
            totalSum += absVal;

            if (absVal < minAbs)
                minAbs = absVal;
        }
    }

    if (negCount % 2 != 0)
        totalSum -= 2LL * minAbs;

    return totalSum;
}
