#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef long long ll;

typedef struct {
    double key;
    int count;
} Inner1;  // for b in cnt1[k][b]

typedef struct {
    double k;
    int inner_size;
    int inner_cap;
    Inner1* inner;  // dynamic array of (b -> count)
} SlopeEntry;

typedef struct {
    double key;
    int count;
} Inner2;  // for k in cnt2[p][k]

typedef struct {
    int p;
    int inner_size;
    int inner_cap;
    Inner2* inner;  // dynamic array of (k -> count)
} MidEntry;

static unsigned long long hash_double(double x) {
    union { double d; unsigned long long u; } tmp;
    tmp.d = x;
    return tmp.u ^ (tmp.u >> 32);
}

long long countTrapezoids(int** points, int pointsSize, int* pointsColSize) {
    int n = pointsSize;
    if (n < 4) return 0;

    // ---- Parameters ----
    const int MAX_SLOPES = 262147; // prime-ish, > n^2/2 max
    const int MAX_MIDS   = 262147;

    // ---- cnt1: slope k -> map b -> count ----
    int* slope_index = (int*)malloc(MAX_SLOPES * sizeof(int));
    for (int i = 0; i < MAX_SLOPES; ++i) slope_index[i] = -1;

    SlopeEntry* slopes = (SlopeEntry*)malloc((n * (n - 1) / 2) * sizeof(SlopeEntry));
    int slopes_count = 0;

    // ---- cnt2: midpoint p -> map slope k -> count ----
    int* mid_index = (int*)malloc(MAX_MIDS * sizeof(int));
    for (int i = 0; i < MAX_MIDS; ++i) mid_index[i] = -1;

    MidEntry* mids = (MidEntry*)malloc((n * (n - 1) / 2) * sizeof(MidEntry));
    int mids_count = 0;

    // ---- Build cnt1 and cnt2 ----
    for (int i = 0; i < n; ++i) {
        int x1 = points[i][0];
        int y1 = points[i][1];
        for (int j = 0; j < i; ++j) {
            int x2 = points[j][0];
            int y2 = points[j][1];

            int dx = x2 - x1;
            int dy = y2 - y1;

            double k, b;
            if (dx == 0) {
                k = 1e9;          // vertical line slope sentinel
                b = (double)x1;   // use x = constant
            } else {
                k = (double)dy / (double)dx;
                // b = (y1*dx - x1*dy)/dx as double, with 64-bit intermediate
                long long num = (long long)y1 * dx - (long long)x1 * dy;
                b = (double)num / (double)dx;
            }
            // normalize -0.0 to +0.0 to keep hash/equality consistent
            if (k == 0.0) k = 0.0;
            if (b == 0.0) b = 0.0;

            // ---- cnt1[k][b]++ ----
            {
                unsigned long long h = hash_double(k);
                int idx = (int)(h % MAX_SLOPES);
                if (idx < 0) idx += MAX_SLOPES;

                int found = -1;
                while (1) {
                    int si = slope_index[idx];
                    if (si == -1) {
                        // new slope entry
                        si = slopes_count++;
                        slope_index[idx] = si;
                        slopes[si].k = k;
                        slopes[si].inner_size = 0;
                        slopes[si].inner_cap = 4;
                        slopes[si].inner = (Inner1*)malloc(slopes[si].inner_cap * sizeof(Inner1));
                        found = si;
                        break;
                    }
                    if (slopes[si].k == k) {
                        found = si;
                        break;
                    }
                    idx++;
                    if (idx == MAX_SLOPES) idx = 0;
                }
                SlopeEntry* se = &slopes[found];

                // find b inside inner map (linear scan, small)
                int inner_found = -1;
                for (int t = 0; t < se->inner_size; ++t) {
                    if (se->inner[t].key == b) {
                        inner_found = t;
                        break;
                    }
                }
                if (inner_found == -1) {
                    if (se->inner_size == se->inner_cap) {
                        se->inner_cap *= 2;
                        se->inner = (Inner1*)realloc(se->inner, se->inner_cap * sizeof(Inner1));
                    }
                    se->inner[se->inner_size].key = b;
                    se->inner[se->inner_size].count = 1;
                    se->inner_size++;
                } else {
                    se->inner[inner_found].count++;
                }
            }

            // ---- cnt2[p][k]++ (for parallelograms via midpoint) ----
            int p = (x1 + x2 + 2000) * 4000 + (y1 + y2 + 2000);
            {
                unsigned long long h = (unsigned long long)(unsigned int)p * 11995408973635179863ULL;
                int idx = (int)(h % MAX_MIDS);
                if (idx < 0) idx += MAX_MIDS;

                int found = -1;
                while (1) {
                    int mi = mid_index[idx];
                    if (mi == -1) {
                        mi = mids_count++;
                        mid_index[idx] = mi;
                        mids[mi].p = p;
                        mids[mi].inner_size = 0;
                        mids[mi].inner_cap = 4;
                        mids[mi].inner = (Inner2*)malloc(mids[mi].inner_cap * sizeof(Inner2));
                        found = mi;
                        break;
                    }
                    if (mids[mi].p == p) {
                        found = mi;
                        break;
                    }
                    idx++;
                    if (idx == MAX_MIDS) idx = 0;
                }
                MidEntry* me = &mids[found];

                int inner_found = -1;
                for (int t = 0; t < me->inner_size; ++t) {
                    if (me->inner[t].key == k) {
                        inner_found = t;
                        break;
                    }
                }
                if (inner_found == -1) {
                    if (me->inner_size == me->inner_cap) {
                        me->inner_cap *= 2;
                        me->inner = (Inner2*)realloc(me->inner, me->inner_cap * sizeof(Inner2));
                    }
                    me->inner[me->inner_size].key = k;
                    me->inner[me->inner_size].count = 1;
                    me->inner_size++;
                } else {
                    me->inner[inner_found].count++;
                }
            }
        }
    }

    // ---- Count trapezoids from cnt1 (same slope, different lines) ----
    ll ans = 0;
    for (int i = 0; i < slopes_count; ++i) {
        SlopeEntry* se = &slopes[i];
        int s = 0;
        for (int t = 0; t < se->inner_size; ++t) {
            int c = se->inner[t].count;
            ans += (ll)s * (ll)c;  // s*c accumulates all pairwise products
            s += c;
        }
    }

    // ---- Subtract parallelograms using cnt2 (same midpoint, different slopes) ----
    for (int i = 0; i < mids_count; ++i) {
        MidEntry* me = &mids[i];
        int s = 0;
        for (int t = 0; t < me->inner_size; ++t) {
            int c = me->inner[t].count;
            ans -= (ll)s * (ll)c;
            s += c;
        }
    }

    // ---- cleanup ----
    for (int i = 0; i < slopes_count; ++i) {
        free(slopes[i].inner);
    }
    for (int i = 0; i < mids_count; ++i) {
        free(mids[i].inner);
    }
    free(slopes);
    free(mids);
    free(slope_index);
    free(mid_index);

    return (int)ans;
}
