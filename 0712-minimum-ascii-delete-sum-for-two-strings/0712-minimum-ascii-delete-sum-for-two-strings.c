int minimumDeleteSum(char * s1, char * s2){
    int m = strlen(s1);
    int n = strlen(s2);
    // dp[i][j] = minimum ASCII delete sum to make s1[0..i-1] and s2[0..j-1] equal
    int dp[m+1][n+1];
    
    // when s2 is empty: delete all chars of s1
    dp[0][0] = 0;
    for(int i = 1; i <= m; i++){
        dp[i][0] = dp[i-1][0] + (int)s1[i-1];
    }
    // when s1 is empty: delete all chars of s2
    for(int j = 1; j <= n; j++){
        dp[0][j] = dp[0][j-1] + (int)s2[j-1];
    }
    
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            if(s1[i-1] == s2[j-1]){
                // if chars match, no cost — take previous
                dp[i][j] = dp[i-1][j-1];
            } else {
                // delete from s1 or delete from s2
                int cost1 = dp[i-1][j] + (int)s1[i-1];
                int cost2 = dp[i][j-1] + (int)s2[j-1];
                dp[i][j] = cost1 < cost2 ? cost1 : cost2;
            }
        }
    }
    
    return dp[m][n];
}
