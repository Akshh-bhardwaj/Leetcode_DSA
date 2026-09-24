long long largestSquareArea(
    int** bottomLeft, int bottomLeftSize, int* bottomLeftColSize,
    int** topRight, int topRightSize, int* topRightColSize
) {
    long long maxArea = 0;

    for (int i = 0; i < bottomLeftSize; i++) {
        for (int j = i + 1; j < bottomLeftSize; j++) {

            int left   = bottomLeft[i][0] > bottomLeft[j][0]
                         ? bottomLeft[i][0] : bottomLeft[j][0];
            int bottom = bottomLeft[i][1] > bottomLeft[j][1]
                         ? bottomLeft[i][1] : bottomLeft[j][1];
            int right  = topRight[i][0] < topRight[j][0]
                         ? topRight[i][0] : topRight[j][0];
            int top    = topRight[i][1] < topRight[j][1]
                         ? topRight[i][1] : topRight[j][1];

            if (right > left && top > bottom) {
                long long width  = (long long)(right - left);
                long long height = (long long)(top - bottom);
                long long side   = width < height ? width : height;
                long long area   = side * side;

                if (area > maxArea) {
                    maxArea = area;
                }
            }
        }
    }

    return maxArea;
}
