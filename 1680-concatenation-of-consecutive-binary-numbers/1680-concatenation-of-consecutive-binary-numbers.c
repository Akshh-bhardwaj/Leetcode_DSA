#define MOD 1000000007

int concatenatedBinary(int n){

    int len = 0;
    long long ans = 0;

    for(int i = 1; i <= n; i++){
        if((i & (i-1)) == 0){
            len++;
        }

        ans = (ans << len) % MOD;

        ans = (ans + i) % MOD;
    }


    return ans;

}