class Solution {
    public int maxSubarrayLength(int[] nums, int k) {
        int maxLen = 0;
        int n = nums.length;
        int left = 0;
        int right = 0;

        HashMap<Integer, Integer> hm = new HashMap<>();

        while (right < n) {
            hm.put(
                nums[right],
                hm.getOrDefault(nums[right], 0) + 1
            );

            while (hm.get(nums[right]) > k) {
                hm.put(
                    nums[left],
                    hm.getOrDefault(nums[left], 0) - 1
                );

                left++;
            }

            maxLen = Math.max(
                maxLen,
                right - left + 1
            );

            right++;
        }

        return maxLen;
    }
}