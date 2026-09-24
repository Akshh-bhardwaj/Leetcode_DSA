#include <stdbool.h>

int findFinalValue(int* nums, int numsSize, int original) {
    bool changed = true;

    while (changed) {
        changed = false;
        for (int i = 0; i < numsSize; i++) {
            if (nums[i] == original) {
                original *= 2;
                changed = true;
                break;   // restart scanning after update
            }
        }
    }

    return original;
}
