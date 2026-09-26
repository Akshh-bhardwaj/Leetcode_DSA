class Solution {
    public int longestSubarray(int[] nums, int k) {
        // k = 3000
        // n = 1e5 
        // so N^2 will not work here. 
        // what if at each index we store what is prefixSum different value's? 
        // how many different can we have?? see if it exceeds k then we take modulo 
        // N * k 
        // say at a index i if I have reminder k, then what earlier positions has same reminder? 
        // sum = p[r] - p[l] // 1 index base d
        // if in (l, r) we change any one 
        // then nw_sum = p[r] - p[l] - 2 * nums[x] 
        // now for nw_sum % k == 0 => p[r] % k = (p[l] + 2 * nums[j]) % k 
        // we can precalculate the (2 * nums[j]) % k = d 

        // p[r] % k == (p[l] % k + change % k) % k 
        int n = nums.length; 
        // we can have r fixed, and change fixed <= 3000, then we need to find `l` - how? 
        // for each reminder store the earliest index - it will give us best length 
        // p[l] % k = (p[r] - d + k) % k 

        //----------
        int f[] = new int[k], l[] = new int[k]; // first and last occ of each reminder 
        Arrays.fill(l, -1); 
        Arrays.fill(f, n + 1); 
        int ans = 0; 
        // at which index we get same reminder 
        List<Integer>[] pos = new ArrayList[k]; 
        for(int d = 0; d < k; d++) pos[d] = new ArrayList<>(); 
        int p[] = new int[n + 1]; 
        for(int i = 0; i < n; i++) {
            p[i + 1] = (((p[i] + nums[i]) % k) + k) %k; 
            int d = (((2 * nums[i]) % k) + k) % k; 
            pos[d].add(i); 
        }

        for(int i = 0 ; i <= n; i++) {
            f[p[i]] = Math.min(f[p[i]], i); 
            l[p[i]] = i; 
        }
        // no negation 
        for (int rem = 0; rem < k; rem++) {
            if (f[rem] != n + 1) {
                ans = Math.max(ans, l[rem] - f[rem]);
            }
        }

        // now for each d
        for(int d = 0; d < k; d++) {
            List<Integer> idx = pos[d]; 
            if(idx.size() == 0) continue; 

            for(int x = 0; x < k; x++) { // left reminder 
                if(f[x] == n + 1) continue; 
                int left = f[x]; 
                int right = l[(x + d) % k]; 

                // biggest value greater than x in reqRem, last value?? 
                if(right <= left) continue; 
                int id = Collections.binarySearch(idx, left); 
                if(id < 0) {
                    id = -id -1; 
                }
                if(id < idx.size() && idx.get(id)< right) {
                    ans = Math.max(ans, right -left);
                }
            }
        }



        // sum = p[r] - p[l] 
        // if we negative 
        return ans; 
    }
}