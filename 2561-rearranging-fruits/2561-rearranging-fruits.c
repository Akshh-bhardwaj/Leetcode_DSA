#include <stdlib.h>
#include <string.h>

int cmp_int(const void *a, const void *b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x < y) ? -1 : (x > y);
}

long long minCost(int* basket1, int basket1Size, int* basket2, int basket2Size){
    int n = basket1Size;
    // sort copies in-place
    qsort(basket1, n, sizeof(int), cmp_int);
    qsort(basket2, n, sizeof(int), cmp_int);

    // check total counts parity by merging unique runs
    // we'll walk through basket1 and basket2 to produce (value, count1) and (value, count2)
    int i = 0, j = 0;
    // temporary arrays for swapped values (imbalance list)
    int *swapped = (int*)malloc(sizeof(int) * 2 * n); // safe upper bound
    int sw_sz = 0;

    while (i < n || j < n) {
        int v;
        int cnt1 = 0, cnt2 = 0;
        if (i < n && (j == n || basket1[i] < basket2[j])) {
            v = basket1[i];
            while (i < n && basket1[i] == v) {
                cnt1++; i++;
            }
        } else if (j < n && (i == n || basket2[j] < basket1[i])) {
            v = basket2[j];
            while (j < n && basket2[j] == v) {
                cnt2++; j++;
            }
        } else { // both valid and equal
            v = basket1[i];
            while (i < n && basket1[i] == v) {
                cnt1++; i++;
            }
            while (j < n && basket2[j] == v) {
                cnt2++; j++;
            }
        }
        int total = cnt1 + cnt2;
        if (total % 2 != 0) { // cannot balance
            free(swapped);
            return -1;
        }
        int diff = cnt1 - cnt2;
        if (diff != 0) {
            int times = abs(diff) / 2;
            for (int k = 0; k < times; ++k) {
                swapped[sw_sz++] = v;
            }
        }
    }

    if (sw_sz == 0) {
        free(swapped);
        return 0;
    }
    // swapped now contains imbalance numbers; we will take first half after sorting
    qsort(swapped, sw_sz, sizeof(int), cmp_int);
    long long global_min = (basket1[0] < basket2[0]) ? basket1[0] : basket2[0];
    long long cost = 0;
    int half = sw_sz / 2;
    for (int k = 0; k < half; ++k) {
        long long x = swapped[k];
        long long use = x < 2 * global_min ? x : 2 * global_min;
        cost += use;
    }
    free(swapped);
    return cost;
}
