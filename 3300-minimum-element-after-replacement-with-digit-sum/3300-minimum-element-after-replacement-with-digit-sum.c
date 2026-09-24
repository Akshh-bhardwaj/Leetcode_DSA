int minElement(int* nums, int numsSize) {
    int minimumElement = INT_MAX;

    for(int i = 0; i < numsSize; i++) {
        int curNum = nums[i];
        int digitsSum = 0;
        while(curNum) {
            digitsSum += curNum % 10;
            curNum /= 10;
        }
        minimumElement = fmin(minimumElement, digitsSum);
    }
    return minimumElement;
}