#include <stdlib.h>
#include <limits.h>

typedef struct {
    int node;
    long long dist;
} HeapNode;

typedef struct {
    HeapNode *data;
    int size;
    int cap;
} MinHeap;

/* ---------- Min Heap ---------- */

MinHeap* createHeap(int cap) {
    MinHeap* h = (MinHeap*)malloc(sizeof(MinHeap));
    h->data = (HeapNode*)malloc(sizeof(HeapNode) * cap);
    h->size = 0;
    h->cap = cap;
    return h;
}

void heapPush(MinHeap* h, int node, long long dist) {
    if (h->size == h->cap) {
        h->cap *= 2;
        h->data = (HeapNode*)realloc(h->data, sizeof(HeapNode) * h->cap);
    }
    int i = h->size++;
    h->data[i].node = node;
    h->data[i].dist = dist;

    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->data[p].dist <= h->data[i].dist) break;
        HeapNode t = h->data[p];
        h->data[p] = h->data[i];
        h->data[i] = t;
        i = p;
    }
}

HeapNode heapPop(MinHeap* h) {
    HeapNode res = h->data[0];
    h->data[0] = h->data[--h->size];

    int i = 0;
    while (1) {
        int l = 2 * i + 1, r = 2 * i + 2, s = i;
        if (l < h->size && h->data[l].dist < h->data[s].dist) s = l;
        if (r < h->size && h->data[r].dist < h->data[s].dist) s = r;
        if (s == i) break;
        HeapNode t = h->data[i];
        h->data[i] = h->data[s];
        h->data[s] = t;
        i = s;
    }
    return res;
}

/* ---------- Graph ---------- */

typedef struct {
    int to;
    long long cost;
} Edge;

Edge **adj;
int *adjSize;
int *adjCap;

void addEdge(int u, int v, long long w) {
    if (adjSize[u] == adjCap[u]) {
        adjCap[u] = adjCap[u] == 0 ? 2 : adjCap[u] * 2;
        adj[u] = (Edge*)realloc(adj[u], sizeof(Edge) * adjCap[u]);
    }
    adj[u][adjSize[u]].to = v;
    adj[u][adjSize[u]].cost = w;
    adjSize[u]++;
}

/* ---------- Solution ---------- */

int minCost(int n, int** edges, int edgesSize, int* edgesColSize) {
    adj = (Edge**)calloc(n, sizeof(Edge*));
    adjSize = (int*)calloc(n, sizeof(int));
    adjCap = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];
        addEdge(u, v, w);         // original edge
        addEdge(v, u, 2LL * w);   // reversed edge
    }

    long long *dist = (long long*)malloc(sizeof(long long) * n);
    for (int i = 0; i < n; i++) dist[i] = LLONG_MAX;
    dist[0] = 0;

    MinHeap* heap = createHeap(16);
    heapPush(heap, 0, 0);

    while (heap->size > 0) {
        HeapNode cur = heapPop(heap);
        int u = cur.node;
        long long d = cur.dist;

        if (d > dist[u]) continue;
        if (u == n - 1) break;

        for (int i = 0; i < adjSize[u]; i++) {
            int v = adj[u][i].to;
            long long nd = d + adj[u][i].cost;
            if (nd < dist[v]) {
                dist[v] = nd;
                heapPush(heap, v, nd);
            }
        }
    }

    long long ans = dist[n - 1];

    // cleanup
    for (int i = 0; i < n; i++) free(adj[i]);
    free(adj);
    free(adjSize);
    free(adjCap);
    free(dist);
    free(heap->data);
    free(heap);

    return ans == LLONG_MAX ? -1 : (int)ans;
}
