#include <stdio.h>

int longestSubarray(int* nums, int numsSize) {
    int max_val = nums[0];
    
    // Step 1: Find the maximum element
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > max_val) {
            max_val = nums[i];
        }
    }

    // Step 2: Find longest contiguous subarray with max_val
    int max_len = 0;
    int current_len = 0;
    
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == max_val) {
            current_len++;
            if (current_len > max_len) {
                max_len = current_len;
            }
        } else {
            current_len = 0;
        }
    }

    return max_len;
}
