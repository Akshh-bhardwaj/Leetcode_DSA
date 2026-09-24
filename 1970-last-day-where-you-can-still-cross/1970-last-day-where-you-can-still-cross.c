#include <stdbool.h>
#include <stdlib.h>

int directions[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};

bool canCross(int row, int col, int** cells, int mid) {
    int total = row * col;

    // allocate grid
    int **grid = (int**)malloc(row * sizeof(int*));
    for (int i = 0; i < row; i++) {
        grid[i] = (int*)calloc(col, sizeof(int));
    }

    // mark water up to day mid
    for (int i = 0; i < mid; i++) {
        int r = cells[i][0] - 1;
        int c = cells[i][1] - 1;
        grid[r][c] = 1;
    }

    // queue for BFS
    int *queue = (int*)malloc(total * sizeof(int));
    int head = 0, tail = 0;

    bool **visited = (bool**)malloc(row * sizeof(bool*));
    for (int i = 0; i < row; i++) {
        visited[i] = (bool*)calloc(col, sizeof(bool));
    }

    // enqueue all land cells in top row
    for (int j = 0; j < col; j++) {
        if (grid[0][j] == 0) {
            queue[tail++] = 0 * col + j;
            visited[0][j] = true;
        }
    }

    // BFS from top to bottom
    while (head < tail) {
        int pos = queue[head++];
        int r = pos / col;
        int c = pos % col;
        if (r == row - 1) return true;

        for (int d = 0; d < 4; d++) {
            int nr = r + directions[d][0];
            int nc = c + directions[d][1];
            if (nr >= 0 && nr < row && nc >= 0 && nc < col &&
                !visited[nr][nc] && grid[nr][nc] == 0) {
                visited[nr][nc] = true;
                queue[tail++] = nr * col + nc;
            }
        }
    }
    return false;
}

int latestDayToCross(int row, int col, int** cells, int cellsSize, int* cellsColSize) {
    int left = 1, right = cellsSize, ans = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (canCross(row, col, cells, mid)) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return ans;
}
