int findMin(int* nums, int numsSize) {
    int lo = 0;
    int hi = numsSize - 1;

    if (nums[lo] < nums[hi]) {
        return nums[lo];
    }

    while (hi - lo > 1) {
        int mid = (lo + hi) >> 1;

        if (nums[mid] > nums[lo]) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    return (nums[lo] < nums[hi]) ? nums[lo] : nums[hi];
}