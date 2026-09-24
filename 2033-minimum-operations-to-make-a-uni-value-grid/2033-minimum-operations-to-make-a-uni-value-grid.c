int minOperations(int** grid, int gridSize, int* gridColSize, int x) {
    

    int count = 0;
    int total = gridSize*(*gridColSize);
    int* gridSort = (int*)malloc(total*sizeof(int));

    int cmp(const void *a,const void *b){
        return (*(int*)a)-(*(int*)b);
    }

    int index = 0; 
    for(int i=0;i<gridSize;i++){
        for(int j=0;j<*gridColSize;j++){
            gridSort[index++] = grid[i][j];
        }  
    }
    // [2, 4, 6, 8]
    int mod = gridSort[0] % x; //2 % 2 = 0
    for(int i=0;i<total;i++){ 
        if(gridSort[i] % x != mod){ 
            return -1;
        }
    }

    qsort(gridSort,total,sizeof(int),cmp);
    int mid = gridSort[total/2];
    
    for(int i=0;i<total;i++){
        count += (abs(gridSort[i]-mid)) / x;
    }
    
    return count;

}