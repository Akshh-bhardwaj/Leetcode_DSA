#include <stdbool.h>
#include <stdlib.h>

int countUnguarded(int m, int n, int** guards, int guardsSize, int* guardsColSize,
                   int** walls, int wallsSize, int* wallsColSize) {
    // 0 = empty, 1 = guarded, 2 = guard or wall
    int *grid = (int*)malloc(m * n * sizeof(int));
    for (int i = 0; i < m * n; i++) grid[i] = 0;
    
    // mark guards
    for (int k = 0; k < guardsSize; k++) {
        int r = guards[k][0], c = guards[k][1];
        grid[r * n + c] = 2;
    }
    // mark walls
    for (int k = 0; k < wallsSize; k++) {
        int r = walls[k][0], c = walls[k][1];
        grid[r * n + c] = 2;
    }
    
    // directions: up, right, down, left
    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = { 0, 1, 0, -1};
    
    // for each guard, cast rays in 4 directions
    for (int k = 0; k < guardsSize; k++) {
        int r0 = guards[k][0], c0 = guards[k][1];
        for (int d = 0; d < 4; d++) {
            int r = r0 + dr[d], c = c0 + dc[d];
            while (r >= 0 && r < m && c >= 0 && c < n && grid[r * n + c] != 2) {
                // mark as guarded if empty
                if (grid[r * n + c] == 0) grid[r * n + c] = 1;
                r += dr[d];
                c += dc[d];
            }
        }
    }
    
    // count unguarded = cells that are 0
    int count = 0;
    for (int i = 0; i < m * n; i++) {
        if (grid[i] == 0) count++;
    }
    
    free(grid);
    return count;
}
