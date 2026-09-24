#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007
#define MAXV 100000   // adjust if constraints change

static long long left_cnt[MAXV + 1];
static long long right_cnt[MAXV + 1];

int specialTriplets(int* nums, int numsSize) {
    // reset counts
    for (int i = 0; i <= MAXV; i++) {
        left_cnt[i] = 0;
        right_cnt[i] = 0;
    }

    // fill right side counts
    for (int i = 0; i < numsSize; i++) {
        int v = nums[i];
        if (v >= 0 && v <= MAXV) right_cnt[v]++;
    }

    long long ans = 0;

    for (int j = 0; j < numsSize; j++) {
        int x = nums[j];
        right_cnt[x]--; // remove from right (middle selected)

        long long target = (long long)x * 2;
        if (target <= MAXV) {
            ans = (ans + (left_cnt[target] * right_cnt[target]) % MOD) % MOD;
        }

        left_cnt[x]++; // add to left
    }

    return (int)ans;
}
