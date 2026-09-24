#include <stdbool.h>

int longestBalanced(int* nums, int numsSize) {
    int maxLen = 0;

    for (int i = 0; i < numsSize; i++) {
        int evenCount = 0, oddCount = 0;

        // store distinct values seen so far
        int evenVals[1500], oddVals[1500];
        int eSize = 0, oSize = 0;

        for (int j = i; j < numsSize; j++) {
            int val = nums[j];
            bool found = false;

            if (val % 2 == 0) {
                for (int k = 0; k < eSize; k++) {
                    if (evenVals[k] == val) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    evenVals[eSize++] = val;
                    evenCount++;
                }
            } else {
                for (int k = 0; k < oSize; k++) {
                    if (oddVals[k] == val) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    oddVals[oSize++] = val;
                    oddCount++;
                }
            }

            if (evenCount == oddCount) {
                int len = j - i + 1;
                if (len > maxLen)
                    maxLen = len;
            }
        }
    }
    return maxLen;
}
