#include <stdlib.h>

// Helper to get minimum of two ints.
static inline int min_int(int a, int b) {
    return a < b ? a : b;
}

// Compute steps needed to cover the interval [l, r] starting from startPos.
static inline int steps(int l, int r, int startPos) {
    if (r <= startPos)
        return startPos - l;
    else if (l >= startPos)
        return r - startPos;
    else
        // Either go to left first then to right or right first then to left:
        // min(startPos + r - 2*l, 2*r - startPos - l)
        return min_int(startPos + r - 2 * l, 2 * r - startPos - l);
}

/*
 * LeetCode function signature:
 * fruits: array of [position, amount]
 * fruitsSize: number of rows
 * fruitsColSize: array of column sizes (always length 2 here)
 */
int maxTotalFruits(int** fruits, int fruitsSize, int* fruitsColSize, int startPos, int k) {
    int l = 0;
    int cur = 0;
    int ans = 0;
    for (int r = 0; r < fruitsSize; ++r) {
        cur += fruits[r][1];
        while (l <= r && steps(fruits[l][0], fruits[r][0], startPos) > k) {
            cur -= fruits[l][1];
            l++;
        }
        if (cur > ans) ans = cur;
    }
    return ans;
}
