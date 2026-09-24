int largestRectangleArea(int* heights, int heightsSize) {
    int *stack = (int*)malloc((heightsSize+1)*sizeof(int));
    int top = -1;
    int maxArea = 0;
    for (int i = 0; i <= heightsSize; ++i) {
        int cur = (i == heightsSize ? 0 : heights[i]);
        while (top >= 0 && heights[stack[top]] > cur) {
            int h = heights[stack[top--]];
            int width = (top < 0 ? i : i - stack[top] - 1);
            int area = h * width;
            if (area > maxArea) maxArea = area;
        }
        stack[++top] = i;
    }
    free(stack);
    return maxArea;
}

int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize) {
    if (matrixSize == 0 || matrixColSize == NULL || *matrixColSize == 0) return 0;
    
    int cols = matrixColSize[0];
    int *heights = (int*)calloc(cols, sizeof(int));
    int maxArea = 0;

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == '1') {
                heights[j] += 1;
            } else {
                heights[j] = 0;
            }
        }
        int area = largestRectangleArea(heights, cols);
        if (area > maxArea) maxArea = area;
    }

    free(heights);
    return maxArea;
}
