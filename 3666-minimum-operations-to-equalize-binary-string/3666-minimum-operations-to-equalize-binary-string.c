#include <stdio.h>
#include <string.h>
#include <limits.h>

int ceilDiv(int x, int y) {
    return (x + y - 1) / y;
}

int minOperations(char *S, int K) {
    
    int N = strlen(S);
    int Z = 0;
    
    // Count zeros
    for (int i = 0; i < N; i++) {
        if (S[i] == '0')
            Z++;
    }
    
    // Special case
    if (N == K) {
        if (Z == 0) return 0;
        if (Z == N) return 1;
        return -1;
    }
    
    int ans = INT_MAX;
    
    // Case 1: Z even
    if (Z % 2 == 0) {
        
        int M = ceilDiv(Z, K);
        int temp = ceilDiv(Z, N - K);
        if (temp > M) M = temp;
        
        // Make M even
        if (M % 2 == 1)
            M++;
        
        if (M < ans)
            ans = M;
    }
    
    // Case 2: parity match
    if (Z % 2 == K % 2) {
        
        int M = ceilDiv(Z, K);
        int temp = ceilDiv(N - Z, N - K);
        if (temp > M) M = temp;
        
        // Make M odd
        if (M % 2 == 0)
            M++;
        
        if (M < ans)
            ans = M;
    }
    
    return (ans == INT_MAX ? -1 : ans);
}