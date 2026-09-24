#include <stdlib.h>
#include <limits.h>

#define MAXN 100005

// Fenwick Tree for count and sum
long long bitCnt[MAXN];
long long bitSum[MAXN];
int size;

// Update Fenwick Tree
void update(long long *bit, int i, long long delta) {
    while (i <= size) {
        bit[i] += delta;
        i += i & -i;
    }
}

// Query Fenwick prefix sum
long long query(long long *bit, int i) {
    long long s = 0;
    while (i > 0) {
        s += bit[i];
        i -= i & -i;
    }
    return s;
}

// Find smallest index such that count >= k
int findKth(long long k) {
    int idx = 0;
    for (int bit = 1 << 17; bit > 0; bit >>= 1) {
        int next = idx + bit;
        if (next <= size && bitCnt[next] < k) {
            k -= bitCnt[next];
            idx = next;
        }
    }
    return idx + 1;
}

// Comparison function for qsort
int cmp(const void *a, const void *b) {
    return (*(int *)a) - (*(int *)b);
}

long long minimumCost(int *nums, int n, int k, int dist) {
    int need = k - 1;

    // Coordinate compression
    int *vals = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) vals[i] = nums[i];
    qsort(vals, n, sizeof(int), cmp);

    int *comp = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        int l = 0, r = n - 1;
        while (l <= r) {
            int m = (l + r) / 2;
            if (vals[m] < nums[i]) l = m + 1;
            else r = m - 1;
        }
        comp[i] = l + 1; // 1-based index
    }

    size = n;
    for (int i = 0; i <= size; i++) {
        bitCnt[i] = 0;
        bitSum[i] = 0;
    }

    // Initial window
    for (int i = 1; i <= dist + 1; i++) {
        update(bitCnt, comp[i], 1);
        update(bitSum, comp[i], nums[i]);
    }

    long long ans = LLONG_MAX;

    // Helper to get sum of k smallest
    long long getSumK() {
        int idx = findKth(need);
        long long cnt = query(bitCnt, idx - 1);
        long long sum = query(bitSum, idx - 1);
        long long remain = need - cnt;
        sum += remain * vals[idx - 1];
        return sum;
    }

    ans = getSumK();

    // Sliding window
    for (int i = dist + 2; i < n; i++) {
        // add
        update(bitCnt, comp[i], 1);
        update(bitSum, comp[i], nums[i]);

        // remove
        int rem = i - (dist + 1);
        update(bitCnt, comp[rem], -1);
        update(bitSum, comp[rem], -nums[rem]);

        long long cur = getSumK();
        if (cur < ans) ans = cur;
    }

    free(vals);
    free(comp);

    return nums[0] + ans;
}
