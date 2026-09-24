#include <limits.h>

long long minimumCost(
    char* source,
    char* target,
    char* original,
    int originalSize,
    char* changed,
    int changedSize,
    int* cost,
    int costSize
) {
    const long long INF = LLONG_MAX / 4;
    long long dist[26][26];

    // Initialize distance matrix
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            dist[i][j] = (i == j) ? 0 : INF;
        }
    }

    // Direct transformations
    for (int i = 0; i < costSize; i++) {
        int u = original[i] - 'a';
        int v = changed[i] - 'a';
        if (cost[i] < dist[u][v]) {
            dist[u][v] = cost[i];
        }
    }

    // Floyd–Warshall
    for (int k = 0; k < 26; k++) {
        for (int i = 0; i < 26; i++) {
            if (dist[i][k] == INF) continue;
            for (int j = 0; j < 26; j++) {
                if (dist[k][j] == INF) continue;
                long long nd = dist[i][k] + dist[k][j];
                if (nd < dist[i][j]) {
                    dist[i][j] = nd;
                }
            }
        }
    }

    // Total cost
    long long ans = 0;
    for (int i = 0; source[i]; i++) {
        if (source[i] == target[i]) continue;
        int u = source[i] - 'a';
        int v = target[i] - 'a';
        if (dist[u][v] == INF) return -1;
        ans += dist[u][v];
    }

    return ans;
}
