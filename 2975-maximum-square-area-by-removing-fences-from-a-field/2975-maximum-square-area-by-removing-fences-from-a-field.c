#include <stdlib.h>

#define MOD 1000000007

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int maximizeSquareArea(int m, int n,
                       int* hFences, int hSize,
                       int* vFences, int vSize) {

    // add boundaries
    int *h = (int *)malloc((hSize + 2) * sizeof(int));
    int *v = (int *)malloc((vSize + 2) * sizeof(int));

    for (int i = 0; i < hSize; i++) h[i] = hFences[i];
    for (int i = 0; i < vSize; i++) v[i] = vFences[i];

    h[hSize++] = 1;
    h[hSize++] = m;
    v[vSize++] = 1;
    v[vSize++] = n;

    qsort(h, hSize, sizeof(int), cmp);
    qsort(v, vSize, sizeof(int), cmp);

    // total horizontal gaps count
    int hGapCount = hSize * (hSize - 1) / 2;
    int *hGap = (int *)malloc(hGapCount * sizeof(int));
    int idx = 0;

    // store all horizontal gaps
    for (int i = 0; i < hSize; i++) {
        for (int j = i + 1; j < hSize; j++) {
            hGap[idx++] = h[j] - h[i];
        }
    }

    // sort horizontal gaps
    qsort(hGap, idx, sizeof(int), cmp);

    int maxSide = -1;

    // for each vertical gap, binary search in horizontal gaps
    for (int i = 0; i < vSize; i++) {
        for (int j = i + 1; j < vSize; j++) {
            int d = v[j] - v[i];

            // binary search in hGap
            int l = 0, r = idx - 1;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (hGap[mid] == d) {
                    if (d > maxSide) maxSide = d;
                    break;
                } else if (hGap[mid] < d) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
        }
    }

    free(h);
    free(v);
    free(hGap);

    if (maxSide == -1) return -1;

    long long area = (long long)maxSide * maxSide;
    return (int)(area % MOD);
}
