class Solution {

    private int helper(int[] nums, int k) {
        HashMap<Integer, Integer> mp = new HashMap<>(); 
        mp.put(0, -1); 
        int n = nums.length; 
        int sum = 0; 
        int ans = 0; 
        for(int i = 0; i < n; i++) {
            sum += nums[i]; 

            int key = (sum % k + k) % k; 
            if(mp.containsKey(key)) {
                ans = Math.max(ans, i - mp.get(key)); 
            } else {
                mp.put(key, i); 
            }
        }
        return ans; 
    }
    public int longestSubarray(int[] nums, int k) {
        // without negating 
        // with neg, cons = 1000 -> n * N will work here, k = 1e5 
        int n = nums.length; 
        // Make a value negative one by one
        // prefix + reminder at two positions must be same, then sum divisible by K 
        
        int ans = helper(nums, k); 
        for(int i = 0; i < n; i++) {
            nums[i] = -nums[i]; 
            ans = Math.max(ans, helper(nums, k)); 
            nums[i] = -nums[i]; 
        }
        return ans; 
    }
}