#include <stdlib.h>

int cmp(const void *pa, const void *pb) {
    int *a = *(int **)pa;
    int *b = *(int **)pb;
    if (a[1] != b[1]) return a[1] - b[1];    // sort by end ascending
    return b[0] - a[0];                      // if tie, start descending
}

int intersectionSizeTwo(int** intervals, int intervalsSize, int* intervalsColSize) {
    if (intervalsSize == 0) return 0;
    qsort(intervals, intervalsSize, sizeof(int*), cmp);

    int ans = 0;
    // first and second are the two largest chosen points so far (first < second)
    int first = -1000000000;
    int second = -1000000000;

    for (int i = 0; i < intervalsSize; ++i) {
        int start = intervals[i][0];
        int end = intervals[i][1];

        if (start > second) {
            // need two new points: end-1 and end
            ans += 2;
            first = end - 1;
            second = end;
        } else if (start > first) {
            // interval contains second but not first -> add one point (end)
            ans += 1;
            first = second;
            second = end;
        }
        // otherwise interval already contains both chosen points -> nothing to add
    }

    return ans;
}
