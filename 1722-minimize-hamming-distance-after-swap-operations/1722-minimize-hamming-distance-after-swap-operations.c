#include <stdlib.h>

typedef struct {
    int root;
    int val;
} Element;

int cmp(const void* a, const void* b) {
    Element* ea = (Element*)a;
    Element* eb = (Element*)b;
    if (ea -> root != eb -> root) {
        return ea -> root - eb -> root;
    }
    return ea -> val - eb -> val;
}

int find(int* parent, int i) {
    if (parent[i] == i) {
        return i;
    }
    return parent[i] = find(parent, parent[i]);
}

int minimumHammingDistance(int* source, int sourceSize, int* target, int targetSize, int** allowedSwaps, int allowedSwapsSize, int* allowedSwapsColSize) {
    int n = sourceSize;
    int* parent = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) parent[i] = i;

    for (int i = 0; i < allowedSwapsSize; i++) {
        int u = find(parent, allowedSwaps[i][0]);
        int v = find(parent, allowedSwaps[i][1]);
        if (u != v) parent[u] = v;
    }

    Element* src = (Element*)malloc(n * sizeof(Element));
    Element* tgt = (Element*)malloc(n * sizeof(Element));

    for (int i = 0; i < n; i++) {
        int root = find(parent, i);
        src[i].root = root;
        src[i].val = source[i];
        
        tgt[i].root = root;
        tgt[i].val = target[i];
    }

    qsort(src, n, sizeof(Element), cmp);
    qsort(tgt, n, sizeof(Element), cmp);

    int matches = 0;
    int i = 0, j = 0;
    
    while (i < n && j < n) {
        if (src[i].root < tgt[j].root) {
            i++;
        } else if (src[i].root > tgt[j].root) {
            j++;
        } else {
            if (src[i].val < tgt[j].val) {
                i++;
            } else if (src[i].val > tgt[j].val) {
                j++;
            } else {
                matches++;
                i++;
                j++;
            }
        }
    }

    free(parent);
    free(src);
    free(tgt);

    return n - matches;
}