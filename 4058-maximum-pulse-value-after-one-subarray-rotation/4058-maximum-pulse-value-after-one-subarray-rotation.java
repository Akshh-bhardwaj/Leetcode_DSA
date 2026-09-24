class Solution {
    public long maxValue(int[] nums) {
        int n = nums.length;

        if (n == 1)
            return nums[0];

        long ans = Long.MAX_VALUE;
        long even = nums[0];
        long odd = 0;
        long sum = nums[0];

        for (int i = 1; i < n; i++) {
            if (i % 2 == 0) {
                sum += nums[i];

                even = Math.max(sum, even);
                ans = Math.min(ans, sum - even);
            } else {
                sum -= nums[i];

                odd = Math.max(sum, odd);
                ans = Math.min(ans, sum - odd);
            }
        }

        return sum - 2 * ans;
    }
}