#include <stdlib.h>

#define MOD 1000000007LL

int cmp(const void* a, const void* b) {
    long long da = *(long long*)a;
    long long db = *(long long*)b;
    if (da < db) return -1;
    if (da > db) return 1;
    return 0;
}

long long countTrapezoids(int** points, int pointsSize, int* pointsColSize) {
    long long* ys = (long long*)malloc(sizeof(long long) * pointsSize);
    for (int i = 0; i < pointsSize; i++)
        ys[i] = points[i][1];

    qsort(ys, pointsSize, sizeof(long long), cmp);

    // Count points per y-level
    long long* segs = (long long*)malloc(sizeof(long long) * pointsSize);
    int segCount = 0;

    long long cnt = 1;
    for (int i = 1; i < pointsSize; i++) {
        if (ys[i] == ys[i - 1]) cnt++;
        else {
            if (cnt >= 2) {
                long long s = (cnt * (cnt - 1) / 2) % MOD;
                segs[segCount++] = s;
            }
            cnt = 1;
        }
    }
    // last group
    if (cnt >= 2) {
        long long s = (cnt * (cnt - 1) / 2) % MOD;
        segs[segCount++] = s;
    }

    free(ys);

    if (segCount < 2) {
        free(segs);
        return 0;
    }

    // Sum all pairs segs[i] * segs[j]
    long long ans = 0;
    long long prefix = 0;

    for (int i = 0; i < segCount; i++) {
        ans = (ans + segs[i] * prefix) % MOD;
        prefix = (prefix + segs[i]) % MOD;
    }

    free(segs);
    return ans % MOD;
}
