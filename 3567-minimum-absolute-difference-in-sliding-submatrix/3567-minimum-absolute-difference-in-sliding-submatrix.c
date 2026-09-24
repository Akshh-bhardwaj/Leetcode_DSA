/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#define OFFSET 100000 
#define HSIZE (2*OFFSET+1)

int cmp(const void* a, const void* b)
{
    return *(int*)a-*(int*)b;
}

int checkDiff(int** grid, int row, int col, int k)
{
    int* hash = calloc(HSIZE, sizeof(int));
    int* arr = malloc(sizeof(int)*(k*k));
    int idx = 0;
    for(int i = row; i< (row+k);i++)
    {
        for(int j = col; j< (col+k);j++)
        {
            hash[grid[i][j]+OFFSET]++;
            if(hash[grid[i][j]+OFFSET]==1)
            {
                arr[idx++]=grid[i][j];
            }
        }        
    }

    qsort(arr, idx, sizeof(int), cmp);

    int ans = INT_MAX;
    for(int i=1;i<idx;i++)
    {
        ans = fmin(ans, arr[i]-arr[i-1]);
    }
    free(hash);
    free(arr);
    return (ans==INT_MAX)?0:ans;
}

int** minAbsDiff(int** grid, int gridSize, int* gridColSize, int k, int* returnSize, int** returnColumnSizes) {
    int m = gridSize;
    int n = *gridColSize;
    
    int** ans          = malloc(sizeof(int*)*(m-k+1));
    *returnColumnSizes = malloc(sizeof(int) *(m-k+1));

    for(int i = 0;i< (m-k+1);i++)
    {
        ans[i]=malloc(sizeof(int)* (n-k+1));
        (*returnColumnSizes)[i] = (n-k+1);

        for(int j = 0;j< (n-k+1);j++)
        {
            ans[i][j] = checkDiff(grid, i, j, k);
        }
    }

    *returnSize=(m-k+1);
    return ans;
}