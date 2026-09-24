void dfs(int** isConnected, int n, int* visited, int city) {
    visited[city] = 1;
    for (int j = 0; j < n; j++) {
        if (isConnected[city][j] == 1 && !visited[j]) {
            dfs(isConnected, n, visited, j);
        }
    }
}

int findCircleNum(int** isConnected, int isConnectedSize, int* isConnectedColSize){
    int n = isConnectedSize;
    int* visited = (int*)calloc(n, sizeof(int));
    int provinces = 0;
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(isConnected, n, visited, i);
            provinces++; // each DFS traversal finds one province
        }
    }
    
    free(visited);
    return provinces;
}
