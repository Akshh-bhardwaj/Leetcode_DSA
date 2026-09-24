// LeetCode 1513 - Number of Substrings With Only 1s
#include <stddef.h>

#define MOD 1000000007LL

int numSub(char * s){
    long long ans = 0;
    long long cur = 0; // number of consecutive '1's ending at current position
    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] == '1') {
            cur = (cur + 1) % MOD;
            ans = (ans + cur) % MOD;
        } else {
            cur = 0;
        }
    }
    return (int)ans;
}
