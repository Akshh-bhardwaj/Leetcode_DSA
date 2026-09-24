bool canReach(char* s, int minJump, int maxJump) {
    int n = strlen(s);
    if (s[n - 1] == '1')
        return false;
    bool* dp = (bool*)calloc(n, sizeof(bool));
    dp[0] = true;
    int reach = 0;
    for (int i = 1; i < n; i++) {
        if (i - minJump >= 0) {
            reach += dp[i - minJump];
        }
        if (i - maxJump - 1 >= 0) {
            reach -= dp[i - maxJump - 1];
        }
        if (reach > 0 && s[i] == '0') {
            dp[i] = true;
        }
    }
    bool ans = dp[n - 1];
    free(dp);
    return ans;
}