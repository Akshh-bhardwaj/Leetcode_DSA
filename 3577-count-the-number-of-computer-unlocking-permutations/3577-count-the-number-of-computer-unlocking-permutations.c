#include <stdint.h>
#include <stddef.h>

int countPermutations(int* complexity, int complexitySize){
    const int MOD = 1000000007;
    // If any computer i>0 has complexity <= complexity[0], impossible
    for (int i = 1; i < complexitySize; i++) {
        if (complexity[i] <= complexity[0]) {
            return 0;
        }
    }
    // Otherwise the answer is (n-1)! % MOD
    long long ans = 1;
    for (int i = 1; i < complexitySize; i++) {
        ans = (ans * i) % MOD;
    }
    return (int)ans;
}
