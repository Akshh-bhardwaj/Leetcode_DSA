// LeetCode 1488 - Avoid Flood in The City
// Function signature expected by LeetCode:
// int* avoidFlood(int* rains, int rainsSize, int* returnSize);

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int find_parent(int *parent, int x) {
    if (parent[x] == x) return x;
    parent[x] = find_parent(parent, parent[x]);
    return parent[x];
}
static void union_parent(int *parent, int a, int b) {
    int pa = find_parent(parent, a);
    int pb = find_parent(parent, b);
    parent[pa] = pb;
}

// --- simple open-addressing hash map (key -> last index) ---
// keys: int64 (lake id), vals: int (last day index), used: 0 = empty, 1 = used
typedef struct {
    int cap;
    int *used;
    long long *keys;
    int *vals;
} HashMap;

static int next_pow2(int x) {
    int p = 1;
    while (p < x) p <<= 1;
    return p;
}
static HashMap* hm_create(int n) {
    int cap = next_pow2(n * 2 + 1);
    HashMap *hm = (HashMap*)malloc(sizeof(HashMap));
    hm->cap = cap;
    hm->used = (int*)calloc(cap, sizeof(int));
    hm->keys = (long long*)malloc(sizeof(long long) * cap);
    hm->vals = (int*)malloc(sizeof(int) * cap);
    return hm;
}
static void hm_free(HashMap *hm) {
    if (!hm) return;
    free(hm->used);
    free(hm->keys);
    free(hm->vals);
    free(hm);
}
// simple multiplicative hash for 64-bit key
static inline int hm_hash(HashMap *hm, long long key) {
    uint64_t k = (uint64_t)key;
    // Knuth multiplicative hashing
    uint64_t h = (k * 11400714819323198485llu);
    return (int)(h & (hm->cap - 1));
}
// put (key -> val)
static void hm_put(HashMap *hm, long long key, int val) {
    int idx = hm_hash(hm, key);
    while (hm->used[idx]) {
        if (hm->keys[idx] == key) {
            hm->vals[idx] = val;
            return;
        }
        idx = (idx + 1) & (hm->cap - 1);
    }
    hm->used[idx] = 1;
    hm->keys[idx] = key;
    hm->vals[idx] = val;
}
// returns 1 if found and set *out to value, else 0
static int hm_get(HashMap *hm, long long key, int *out) {
    int idx = hm_hash(hm, key);
    int start = idx;
    while (hm->used[idx]) {
        if (hm->keys[idx] == key) {
            *out = hm->vals[idx];
            return 1;
        }
        idx = (idx + 1) & (hm->cap - 1);
        if (idx == start) break;
    }
    return 0;
}

int* avoidFlood(int* rains, int rainsSize, int* returnSize){
    int n = rainsSize;
    int *res = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) {
        if (rains[i] == 0) res[i] = 1; // default arbitrarily
        else res[i] = -1; // raining day -> -1
    }

    // parent DSU: parent[i] gives next available dry day >= i
    // size n+1, parent[n] == n sentinel meaning no more dry days
    int *parent = (int*)malloc(sizeof(int) * (n + 1));
    for (int i = 0; i <= n; ++i) parent[i] = i;

    // Mark rain-days as initially unavailable in the dry-day DSU by unioning them to next
    // (they will never be dry). Dry days remain as their own parent.
    for (int i = 0; i < n; ++i) {
        if (rains[i] != 0) union_parent(parent, i, i+1);
    }

    // hashmap for last occurrence of each lake
    HashMap *hm = hm_create(n+5);

    for (int i = 0; i < n; ++i) {
        if (rains[i] > 0) {
            long long lake = (long long)rains[i];
            int prevDay;
            if (hm_get(hm, lake, &prevDay)) {
                // need to find a dry day > prevDay and < i (i.e., >= prevDay+1 and <= i-1)
                int candidate = find_parent(parent, prevDay + 1);
                if (candidate >= n || candidate >= i) {
                    // no available dry day before this rain -> impossible
                    *returnSize = 0;
                    hm_free(hm);
                    free(parent);
                    free(res);
                    return NULL;
                }
                // use candidate to dry this lake
                res[candidate] = (int)lake;
                // mark candidate used: union it with candidate+1
                union_parent(parent, candidate, candidate + 1);
            }
            // update last day of lake
            hm_put(hm, lake, i);
            // raining day already set as -1 in res
        } else {
            // dry day: we already set res[i]=1 and it is available via DSU (unless unioned)
            // nothing else to do now
        }
    }

    hm_free(hm);
    free(parent);
    *returnSize = n;
    return res;
}
