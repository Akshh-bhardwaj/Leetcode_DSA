int countCoveredBuildings(int n, int** buildings, int buildingsSize, int* buildingsColSize){
    int ans = 0;

    // Prepare arrays for row/col bounds
    // minY[x]: smallest y seen in row x
    // maxY[x]: largest y seen in row x
    // minX[y]: smallest x seen in col y
    // maxX[y]: largest x seen in col y
    int *minY = (int*)malloc((n+1)*sizeof(int));
    int *maxY = (int*)malloc((n+1)*sizeof(int));
    int *minX = (int*)malloc((n+1)*sizeof(int));
    int *maxX = (int*)malloc((n+1)*sizeof(int));
    if(!minY || !maxY || !minX || !maxX) return 0;

    for(int i=1;i<=n;i++){
        minY[i] = n+1;
        maxY[i] = 0;
        minX[i] = n+1;
        maxX[i] = 0;
    }

    // First pass: update bounds
    for(int i=0;i<buildingsSize;i++){
        int x = buildings[i][0];
        int y = buildings[i][1];
        if(y < minY[x]) minY[x] = y;
        if(y > maxY[x]) maxY[x] = y;
        if(x < minX[y]) minX[y] = x;
        if(x > maxX[y]) maxX[y] = x;
    }

    // Second pass: count covered
    for(int i=0;i<buildingsSize;i++){
        int x = buildings[i][0];
        int y = buildings[i][1];
        if(minY[x] < y && y < maxY[x] &&
           minX[y] < x && x < maxX[y]){
            ans++;
        }
    }

    free(minY);
    free(maxY);
    free(minX);
    free(maxX);
    return ans;
}
