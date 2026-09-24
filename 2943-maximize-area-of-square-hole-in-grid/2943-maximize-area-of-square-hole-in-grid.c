#include <stdlib.h>

/* ✅ FUNCTION PROTOTYPE (IMPORTANT) */
int maximizeSquareHoleArea(int n, int m, int* hBars, int hSize, int* vBars, int vSize);

int cmpfunc(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int maximizeSquareHoleArea(int n, int m, int* hBars, int hSize, int* vBars, int vSize) {
    qsort(hBars, hSize, sizeof(int), cmpfunc);
    qsort(vBars, vSize, sizeof(int), cmpfunc);

    int maxH = 1, curH = 1;
    for (int i = 1; i < hSize; i++) {
        if (hBars[i] == hBars[i - 1] + 1) {
            curH++;
            if (curH > maxH) maxH = curH;
        } else {
            curH = 1;
        }
    }

    int maxV = 1, curV = 1;
    for (int i = 1; i < vSize; i++) {
        if (vBars[i] == vBars[i - 1] + 1) {
            curV++;
            if (curV > maxV) maxV = curV;
        } else {
            curV = 1;
        }
    }

    int side = (maxH < maxV ? maxH : maxV) + 1;
    return side * side;
}
