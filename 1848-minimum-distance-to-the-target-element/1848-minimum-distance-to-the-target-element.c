int getMinDistance(int* nums, int numsSize, int target, int start) {
    int min_dist = INT_MAX;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == target) {
            int diff = abs(i - start);
            if (diff < min_dist) {
                min_dist = diff;
            }
        }
    }
    return min_dist;
}