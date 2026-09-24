#include <stdlib.h>

#define MOD 1000000007

// ---------- Fenwick (BIT) for counts over compressed values ----------

static void bit_update(int *bit, int n, int idx, int delta) {
    for (; idx <= n; idx += idx & -idx)
        bit[idx] += delta;
}

static int bit_sum(int *bit, int idx) {
    int res = 0;
    for (; idx > 0; idx -= idx & -idx)
        res += bit[idx];
    return res;
}

// Find smallest index i such that prefix sum >= k (1-based)
// Assumes 1 <= k <= totalCount stored in BIT.
static int bit_find_kth(int *bit, int n, int k) {
    int idx = 0;
    // largest power of two <= n
    int bitMask = 1;
    while ((bitMask << 1) <= n) bitMask <<= 1;

    for (int step = bitMask; step > 0; step >>= 1) {
        int next = idx + step;
        if (next <= n && bit[next] < k) {
            idx = next;
            k -= bit[next];
        }
    }
    return idx + 1; // 1-based index
}

// ---------- Helpers for coordinate compression ----------

static int cmp_int(const void *a, const void *b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

// lower_bound on sorted array arr[0..n-1]
static int lower_bound_int(int *arr, int n, int val) {
    int l = 0, r = n; // [l, r)
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] < val) l = mid + 1;
        else r = mid;
    }
    return l; // first index with arr[idx] >= val
}

// ---------- Main solution ----------

int countPartitions(int* nums, int numsSize, int k){
    int n = numsSize;
    if (n == 0) return 0;

    // Coordinate compression of nums values
    int *vals = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) vals[i] = nums[i];
    qsort(vals, n, sizeof(int), cmp_int);

    int m = 0; // number of unique values
    for (int i = 0; i < n; ++i) {
        if (i == 0 || vals[i] != vals[i-1]) {
            vals[m++] = vals[i];
        }
    }

    // Fenwick tree over counts of compressed values
    int *bit = (int*)calloc(m + 1, sizeof(int));
    int totalCount = 0; // total number of elements in current window

    // dp[i] = number of ways to partition nums[0..i-1]
    long long *dp = (long long*)malloc((n + 1) * sizeof(long long));
    long long *pref = (long long*)malloc((n + 1) * sizeof(long long));

    dp[0] = 1;       // empty prefix has 1 way
    pref[0] = 1;

    int left = 1;    // 1-based index of left side of current window

    for (int right = 1; right <= n; ++right) {
        // Add nums[right-1] to window
        int v = nums[right - 1];
        int pos = lower_bound_int(vals, m, v); // 0-based
        int idx = pos + 1;                     // BIT is 1-based
        bit_update(bit, m, idx, 1);
        totalCount++;

        // Shrink from left while window max-min > k
        while (totalCount > 0) {
            // min value in window
            int minIdx = bit_find_kth(bit, m, 1);
            int maxIdx = bit_find_kth(bit, m, totalCount);
            int minVal = vals[minIdx - 1];
            int maxVal = vals[maxIdx - 1];

            if (maxVal - minVal <= k) break;

            // Remove nums[left-1] and move left++
            int v2 = nums[left - 1];
            int pos2 = lower_bound_int(vals, m, v2);
            int idx2 = pos2 + 1;
            bit_update(bit, m, idx2, -1);
            totalCount--;
            left++;
        }

        // Now window [left..right] is valid: any start j in [left..right]
        // gives last segment [j..right] valid.
        // So dp[right] = sum_{t = left-1..right-1} dp[t]
        long long ways = pref[right - 1];
        if (left >= 2) ways = (ways - pref[left - 2] + MOD) % MOD;
        dp[right] = ways;
        pref[right] = (pref[right - 1] + dp[right]) % MOD;
    }

    int ans = (int)(dp[n] % MOD);

    free(vals);
    free(bit);
    free(dp);
    free(pref);

    return ans;
}