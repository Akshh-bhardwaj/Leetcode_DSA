#include <stdlib.h>
#include <string.h>

#define MAXN 1005
#define MAXB 1005
#define NEG -1000000000

int *presentG, *futureG;
int head[MAXN], to[MAXN], nxt[MAXN], ecnt;
int B;

int dp0[MAXN][MAXB], dp1[MAXN][MAXB], dp2[MAXN][MAXB];

int max(int a, int b) { return a > b ? a : b; }

void addEdge(int u, int v) {
    to[ecnt] = v;
    nxt[ecnt] = head[u];
    head[u] = ecnt++;
}

void dfs(int u, int isRoot) {
    for (int i = 0; i <= B; i++)
        dp0[u][i] = dp1[u][i] = dp2[u][i] = NEG;

    dp0[u][0] = 0;

    int full = presentG[u];
    int disc = full / 2;

    if (full <= B)
        dp1[u][full] = futureG[u] - full;

    // ✅ discount only if NOT root
    if (!isRoot && disc <= B)
        dp2[u][disc] = futureG[u] - disc;

    for (int e = head[u]; e != -1; e = nxt[e]) {
        int v = to[e];
        dfs(v, 0);

        int n0[MAXB], n1[MAXB], n2[MAXB];
        for (int i = 0; i <= B; i++)
            n0[i] = n1[i] = n2[i] = NEG;

        for (int i = 0; i <= B; i++) {
            for (int j = 0; i + j <= B; j++) {

                if (dp0[u][i] != NEG)
                    n0[i + j] = max(n0[i + j],
                        dp0[u][i] + max(dp0[v][j], dp1[v][j]));

                if (dp1[u][i] != NEG)
                    n1[i + j] = max(n1[i + j],
                        dp1[u][i] + max(dp0[v][j], dp2[v][j]));

                if (dp2[u][i] != NEG)
                    n2[i + j] = max(n2[i + j],
                        dp2[u][i] + max(dp0[v][j], dp2[v][j]));
            }
        }

        for (int i = 0; i <= B; i++) {
            dp0[u][i] = n0[i];
            dp1[u][i] = n1[i];
            dp2[u][i] = n2[i];
        }
    }
}

int maxProfit(
    int n,
    int* present, int presentSize,
    int* future, int futureSize,
    int** hierarchy, int hierarchySize,
    int* hierarchyColSize,
    int budget
) {
    presentG = present;
    futureG = future;
    B = budget;

    memset(head, -1, sizeof(head));
    ecnt = 0;

    for (int i = 0; i < hierarchySize; i++)
        addEdge(hierarchy[i][0] - 1, hierarchy[i][1] - 1);

    dfs(0, 1); // CEO is root

    int ans = 0;
    for (int i = 0; i <= B; i++) {
        ans = max(ans, dp0[0][i]);
        ans = max(ans, dp1[0][i]);
        ans = max(ans, dp2[0][i]);
    }
    return ans;
}
