#include <stdbool.h>
#include <string.h>
#include <math.h>

bool hasAllCodes(char* s, int k) {
    int n = strlen(s);
    int need = 1 << k;          // total patterns
    bool seen[1 << 20] = {false}; // k <= 20 constraint safe
    int mask = need - 1;
    int hash = 0;
    
    for (int i = 0; i < n; i++) {
        hash = ((hash << 1) & mask) | (s[i] - '0');
        
        if (i >= k - 1 && !seen[hash]) {
            seen[hash] = true;
            need--;
            if (need == 0) return true;
        }
    }
    return false;
}