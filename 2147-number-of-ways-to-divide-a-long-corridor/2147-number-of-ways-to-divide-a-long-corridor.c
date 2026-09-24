#include <stdlib.h>
#include <string.h>

#define MOD 1000000007

int numberOfWays(char* corridor) {
    int seats = 0;
    long long ways = 1;
    int plants = 0;
    int n = strlen(corridor);

    for (int i = 0; i < n; i++) {
        if (corridor[i] == 'S') {
            seats++;

            if (seats > 2 && seats % 2 == 1) {
                ways = (ways * (plants + 1)) % MOD;
                plants = 0;
            }
        } else if (seats % 2 == 0 && seats > 0) {
            plants++;
        }
    }

    if (seats == 0 || seats % 2 != 0) return 0;
    return (int)ways;
}
