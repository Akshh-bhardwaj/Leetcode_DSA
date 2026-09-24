#define MAXN 200001

int pref_sum[MAXN];

int max(int a, int b) {
    return a > b ? a : b;
}

int maxRotateFunction(int* nums, int n){
    pref_sum[0] = nums[0];
    for (int i = 1, ei = 2 * n; i < ei; i++) {
        pref_sum[i] = pref_sum[i - 1] + nums[i % n];
    }
    int s = 0;
    for (int i = 0; i < n; i++) {
        s += i * nums[i];
    }
    int ans = s;
    for (int i = 1; i < n; i++) {
        int current = s - pref_sum[i + n - 2] + pref_sum[i - 1] + nums[i - 1] * (n - 1);
        ans = max(ans, current);
        s = current;
    }
    return ans;
}