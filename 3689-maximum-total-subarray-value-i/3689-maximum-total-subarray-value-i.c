long long maxTotalValue(int* nums, int numsSize, int k) {
    int i;
    long long int max=-1;
    long long int min=9223372036854775807;
    for (i=0; i<numsSize; i++) {
        if(nums[i]>max) {
            max=nums[i];
        }
        if(nums[i]<min) {
            min=nums[i];
        }
    }
    max=k*(max-min);
    return max;
}