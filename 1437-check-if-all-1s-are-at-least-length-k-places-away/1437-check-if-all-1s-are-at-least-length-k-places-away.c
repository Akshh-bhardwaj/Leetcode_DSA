#include <stdbool.h>

bool kLengthApart(int* nums, int numsSize, int k){
    int last = -1e9; // a very small number to indicate "no previous 1 yet"
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] == 1) {
            if (i - last - 1 < k) return false; // not enough zeros between this 1 and the previous 1
            last = i;
        }
    }
    return true;
}
