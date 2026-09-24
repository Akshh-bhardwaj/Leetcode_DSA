class Solution {
    public int smallestIndex(int[] nums) {
        for (int i = 0; i < nums.length; i++) {
            int sum = 0;
            for (int t = nums[i]; t > 0; t /= 10) {
                sum += t % 10;
            }
            if (sum == i) return i;
        }
        return -1;
    }
}