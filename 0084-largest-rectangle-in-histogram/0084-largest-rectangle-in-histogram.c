#include <stdlib.h>

/**
 * @param heights
 * @param heightsSize
 * @return
 */
int largestRectangleArea(int* heights, int heightsSize) {
    int stack[heightsSize + 1];
    int top = -1;
    int maxArea = 0;

    for (int i = 0; i <= heightsSize; i++) {
        int currHeight = (i == heightsSize) ? 0 : heights[i];

        while (top != -1 && currHeight < heights[stack[top]]) {
            int h = heights[stack[top--]];
            int width = (top == -1) ? i : (i - stack[top] - 1);
            int area = h * width;
            if (area > maxArea)
                maxArea = area;
        }
        stack[++top] = i;
    }

    return maxArea;
}
