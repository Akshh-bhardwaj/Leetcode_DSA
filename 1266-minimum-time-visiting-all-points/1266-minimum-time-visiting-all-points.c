int minTimeToVisitAllPoints(int** points, int pointsSize, int* pointsColSize){
    int total = 0;
    for(int i = 1; i < pointsSize; i++){
        int dx = abs(points[i][0] - points[i-1][0]);
        int dy = abs(points[i][1] - points[i-1][1]);
        // In one move, we can reduce both dx and dy by 1 (diagonally),
        // so time = max(dx, dy)
        total += (dx > dy ? dx : dy);
    }
    return total;
}
