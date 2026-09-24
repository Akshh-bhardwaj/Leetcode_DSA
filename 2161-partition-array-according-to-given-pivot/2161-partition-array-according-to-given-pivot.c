int* pivotArray(int* nums, int numsSize, int pivot, int* returnSize) {
    int* result = (int*)malloc(numsSize * sizeof(int));
    int idx = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] < pivot) {
            result[idx++] = nums[i];
        }
    }

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == pivot) {
            result[idx++] = nums[i];
        }
    }

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > pivot) {
            result[idx++] = nums[i];
        }
    }

    *returnSize = numsSize;
    return result;
}