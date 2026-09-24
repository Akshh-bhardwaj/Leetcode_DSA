#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 400005

typedef struct {
    double y, x1, x2;
    int type;
} Event;

typedef struct {
    int cover;
    double len;
} Node;

Event events[MAXN];
double xs[MAXN];
Node seg[MAXN * 4];
int xsSize, eSize;

/* Segment Tree */
void pushUp(int idx, int l, int r) {
    if (seg[idx].cover > 0)
        seg[idx].len = xs[r] - xs[l];
    else if (l + 1 == r)
        seg[idx].len = 0;
    else
        seg[idx].len = seg[idx*2].len + seg[idx*2+1].len;
}

void update(int idx, int l, int r, int ql, int qr, int v) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        seg[idx].cover += v;
        pushUp(idx, l, r);
        return;
    }
    int m = (l + r) / 2;
    update(idx*2, l, m, ql, qr, v);
    update(idx*2+1, m, r, ql, qr, v);
    pushUp(idx, l, r);
}

int cmpEvent(const void* a, const void* b) {
    double d = ((Event*)a)->y - ((Event*)b)->y;
    return (d > 0) - (d < 0);
}

int cmpDouble(const void* a, const void* b) {
    double d = *(double*)a - *(double*)b;
    return (d > 0) - (d < 0);
}

int lowerBound(double* arr, int n, double x) {
    int l = 0, r = n;
    while (l < r) {
        int m = (l + r) / 2;
        if (arr[m] < x) l = m + 1;
        else r = m;
    }
    return l;
}

double separateSquares(int** squares, int n, int* colSize) {
    xsSize = eSize = 0;

    for (int i = 0; i < n; i++) {
        double x = squares[i][0];
        double y = squares[i][1];
        double l = squares[i][2];

        events[eSize++] = (Event){y, x, x+l, +1};
        events[eSize++] = (Event){y+l, x, x+l, -1};

        xs[xsSize++] = x;
        xs[xsSize++] = x+l;
    }

    qsort(xs, xsSize, sizeof(double), cmpDouble);
    int k = 0;
    for (int i = 0; i < xsSize; i++)
        if (i == 0 || xs[i] != xs[i-1])
            xs[k++] = xs[i];
    xsSize = k;

    qsort(events, eSize, sizeof(Event), cmpEvent);
    memset(seg, 0, sizeof(seg));

    double total = 0.0;
    double prevY = events[0].y;

    for (int i = 0; i < eSize; i++) {
        double dy = events[i].y - prevY;
        total += seg[1].len * dy;

        int l = lowerBound(xs, xsSize, events[i].x1);
        int r = lowerBound(xs, xsSize, events[i].x2);
        update(1, 0, xsSize-1, l, r, events[i].type);

        prevY = events[i].y;
    }

    double half = total / 2.0;
    memset(seg, 0, sizeof(seg));
    prevY = events[0].y;
    double acc = 0.0;

    for (int i = 0; i < eSize; i++) {
        double dy = events[i].y - prevY;
        double area = seg[1].len * dy;

        if (acc + area >= half) {
            return prevY + (half - acc) / seg[1].len;
        }

        acc += area;
        int l = lowerBound(xs, xsSize, events[i].x1);
        int r = lowerBound(xs, xsSize, events[i].x2);
        update(1, 0, xsSize-1, l, r, events[i].type);
        prevY = events[i].y;
    }
    return prevY;
}
