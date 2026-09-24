// LeetCode 2654 - C solution
#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int minOperations(int* nums, int numsSize){
    int n = numsSize;
    if (n == 0) return -1;

    // Count ones
    int ones = 0;
    for (int i = 0; i < n; ++i) if (nums[i] == 1) ++ones;
    if (ones > 0) return n - ones;

    // Find shortest subarray with gcd == 1
    int minOps = INT_MAX;
    for (int i = 0; i < n; ++i) {
        int g = nums[i];
        if (g == 1) { // defensive, though we handled ones above
            minOps = 0;
            break;
        }
        for (int j = i + 1; j < n; ++j) {
            g = gcd(g, nums[j]);
            if (g == 1) {
                int ops = j - i; // number of pairwise gcd-operations needed to produce a 1 in this subarray
                if (ops < minOps) minOps = ops;
                break; // no need to extend this i further
            }
        }
    }

    if (minOps == INT_MAX) return -1;
    // After creating a 1 from that subarray we need (n - 1) more ops to make all elements 1
    return minOps + n - 1;
}
