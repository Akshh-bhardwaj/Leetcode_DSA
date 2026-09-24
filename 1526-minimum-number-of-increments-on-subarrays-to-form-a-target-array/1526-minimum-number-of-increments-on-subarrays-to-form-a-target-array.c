#include <stdlib.h>

/*
 LeetCode function signature:
 Given target[] of length targetSize, return minimum number of increments
 on subarrays (each increment adds +1 to every element in chosen subarray)
 to form target from an initial all-zero array.
*/

int minNumberOperations(int* target, int targetSize) {
    if (targetSize <= 0) return 0;
    int ans = 0;
    int prev = 0;
    for (int i = 0; i < targetSize; ++i) {
        if (target[i] > prev) {
            ans += target[i] - prev;
        }
        prev = target[i];
    }
    return ans;
}
