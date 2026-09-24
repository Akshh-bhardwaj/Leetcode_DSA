#define MOD 1000000007

int numOfWays(int n) {
    long long a = 6; // type A for row 1
    long long b = 6; // type B for row 1
    
    for (int i = 2; i <= n; i++) {
        long long newA = (3LL * a + 2LL * b) % MOD;
        long long newB = (2LL * a + 2LL * b) % MOD;
        a = newA;
        b = newB;
    }
    
    return (int)((a + b) % MOD);
}
