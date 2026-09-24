#include <stdlib.h>

int largestMagicSquare(int** grid, int gridSize, int* gridColSize){
    int m = gridSize;
    int n = gridColSize[0];

    // prefixRow[i][j]: sum of row i from col 0 to col j-1
    int prefixRow[51][51];
    // prefixCol[i][j]: sum of col j from row 0 to row i-1
    int prefixCol[51][51];

    for(int i = 0; i < m; ++i){
        prefixRow[i][0] = 0;
        for(int j = 0; j < n; ++j){
            prefixRow[i][j+1] = prefixRow[i][j] + grid[i][j];
        }
    }

    for(int j = 0; j < n; ++j){
        prefixCol[0][j] = 0;
        for(int i = 0; i < m; ++i){
            prefixCol[i+1][j] = prefixCol[i][j] + grid[i][j];
        }
    }

    int maxSide = 1; // 1×1 is always magic

    for(int k = (m < n ? m : n); k >= 2; --k){
        for(int r = 0; r + k <= m; ++r){
            for(int c = 0; c + k <= n; ++c){
                int target = prefixRow[r][c+k] - prefixRow[r][c];

                int sumD1 = 0, sumD2 = 0;
                for(int i = 0; i < k; ++i){
                    sumD1 += grid[r+i][c+i];
                    sumD2 += grid[r+i][c + k - 1 - i];
                }
                if(sumD1 != target || sumD2 != target) continue;

                int ok = 1;
                for(int i = 0; i < k && ok; ++i){
                    int rowSum = prefixRow[r+i][c+k] - prefixRow[r+i][c];
                    if(rowSum != target) ok = 0;
                }
                if(!ok) continue;

                for(int j = 0; j < k && ok; ++j){
                    int colSum = prefixCol[r+k][c+j] - prefixCol[r][c+j];
                    if(colSum != target) ok = 0;
                }

                if(ok) return k;
            }
        }
    }

    return maxSide;
}