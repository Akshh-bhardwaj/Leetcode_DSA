#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INF (INT_MAX / 2)

typedef struct Trie {
    struct Trie* child[26];
    int id;
} Trie;

/* ---------- Trie Utilities ---------- */

Trie* createTrie() {
    Trie* node = (Trie*)malloc(sizeof(Trie));
    for (int i = 0; i < 26; i++) {
        node->child[i] = NULL;
    }
    node->id = -1;
    return node;
}

int add(Trie* node, const char* word, int* index) {
    for (int i = 0; word[i]; i++) {
        int c = word[i] - 'a';
        if (!node->child[c]) {
            node->child[c] = createTrie();
        }
        node = node->child[c];
    }
    if (node->id == -1) {
        node->id = ++(*index);
    }
    return node->id;
}

void update(long long* x, long long y) {
    if (*x == -1 || y < *x) {
        *x = y;
    }
}

/* ---------- Main Solution ---------- */

long long minimumCost(
    char* source,
    char* target,
    char** original,
    int originalSize,
    char** changed,
    int changedSize,
    int* cost,
    int costSize
) {
    int n = strlen(source);
    Trie* root = createTrie();

    /* Max nodes = unique(original + changed) ≤ 2 * originalSize */
    int maxNodes = originalSize * 2 + 5;
    int** G = (int**)malloc(maxNodes * sizeof(int*));
    for (int i = 0; i < maxNodes; i++) {
        G[i] = (int*)malloc(maxNodes * sizeof(int));
        for (int j = 0; j < maxNodes; j++) {
            G[i][j] = (i == j) ? 0 : INF;
        }
    }

    int p = -1;

    /* Build graph */
    for (int i = 0; i < originalSize; i++) {
        int x = add(root, original[i], &p);
        int y = add(root, changed[i], &p);
        if (cost[i] < G[x][y]) {
            G[x][y] = cost[i];
        }
    }

    /* Floyd–Warshall (overflow-safe) */
    for (int k = 0; k <= p; k++) {
        for (int i = 0; i <= p; i++) {
            if (G[i][k] == INF) continue;
            for (int j = 0; j <= p; j++) {
                if (G[k][j] == INF) continue;
                int nd = G[i][k] + G[k][j];
                if (nd < G[i][j]) {
                    G[i][j] = nd;
                }
            }
        }
    }

    /* DP: f[i] = min cost to convert source[0..i] → target[0..i] */
    long long* f = (long long*)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) f[i] = -1;

    for (int j = 0; j < n; j++) {
        if (j > 0 && f[j - 1] == -1) continue;

        long long base = (j == 0 ? 0 : f[j - 1]);

        /* Single character match */
        if (source[j] == target[j]) {
            update(&f[j], base);
        }

        /* Trie-based substring transitions */
        Trie* u = root;
        Trie* v = root;
        for (int i = j; i < n; i++) {
            u = u->child[source[i] - 'a'];
            v = v->child[target[i] - 'a'];
            if (!u || !v) break;

            if (u->id != -1 && v->id != -1 && G[u->id][v->id] != INF) {
                update(&f[i], base + G[u->id][v->id]);
            }
        }
    }

    long long ans = f[n - 1];

    /* Cleanup */
    for (int i = 0; i < maxNodes; i++) {
        free(G[i]);
    }
    free(G);
    free(f);

    return ans;
}
