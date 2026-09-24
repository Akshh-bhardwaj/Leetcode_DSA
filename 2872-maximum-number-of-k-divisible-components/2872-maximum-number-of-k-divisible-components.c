#include <stdlib.h>

typedef struct {
    int to;
    int next;
} Edge;

Edge E[400005];
int head[200005], ecnt;
int K, answer;

// Add bidirectional edge
void addEdge(int u, int v) {
    E[ecnt].to = v;
    E[ecnt].next = head[u];
    head[u] = ecnt++;
}

// DFS function
long long dfs(int node, int parent, int* values) {
    long long sum = values[node];

    for (int i = head[node]; i != -1; i = E[i].next) {
        int nxt = E[i].to;
        if (nxt == parent) continue;
        sum += dfs(nxt, node, values);
    }

    if (sum % K == 0) {
        answer++;
        return 0;  // Cut component here
    }
    return sum;
}

// MAIN LEETCODE FUNCTION
int maxKDivisibleComponents(int n, int** edges, int edgesSize, int* edgesColSize,
                            int* values, int valuesSize, int k) {

    K = k;
    answer = 0;
    ecnt = 0;

    // Initialize adjacency list
    for (int i = 0; i < n; i++)
        head[i] = -1;

    // Build graph
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        addEdge(u, v);
        addEdge(v, u);
    }

    // DFS from node 0 (tree connected)
    dfs(0, -1, values);

    return answer;
}
