// LeetCode 3005 - Count Elements With Maximum Frequency
// Function name must be exactly as LeetCode specifies.

#include <stdlib.h>

int maxFrequencyElements(int* nums, int numsSize){
    // Since 1 <= nums[i] <= 100, we can use a fixed array
    int freq[101] = {0};
    
    // Count frequency of each element
    for (int i = 0; i < numsSize; i++) {
        freq[nums[i]]++;
    }

    // Find maximum frequency
    int mx = 0;
    for (int v = 1; v <= 100; v++) {
        if (freq[v] > mx) mx = freq[v];
    }

    // Count how many elements have frequency == mx
    int ans = 0;
    for (int v = 1; v <= 100; v++) {
        if (freq[v] == mx) ans += freq[v];
    }

    return ans;
}
