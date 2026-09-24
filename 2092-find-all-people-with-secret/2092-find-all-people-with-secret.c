#include <stdio.h>
#include <stdlib.h>

// Union-Find structure
int *parent;

int findp(int x) {
    if (parent[x] != x)
        parent[x] = findp(parent[x]);
    return parent[x];
}

void unite(int x, int y) {
    int px = findp(x);
    int py = findp(y);
    if (px != py) {
        parent[py] = px;
    }
}

int cmp(const void *a, const void *b) {
    int *m1 = *(int **)a;
    int *m2 = *(int **)b;
    return m1[2] - m2[2];
}

int *findAllPeople(int n, int **meetings, int meetingsSize, int *meetingsColSize, int firstPerson, int *returnSize){
    // Add extra meeting for time 0: {0, firstPerson, 0}
    int total = meetingsSize + 1;
    int **all = malloc(sizeof(int *) * total);

    // copy original meetings
    for (int i = 0; i < meetingsSize; i++) {
        all[i] = meetings[i];
    }
    // create a new array for the initial share
    int *init = malloc(sizeof(int)*3);
    init[0] = 0;
    init[1] = firstPerson;
    init[2] = 0;
    all[meetingsSize] = init;

    // sort all meetings by time
    qsort(all, total, sizeof(int *), cmp);

    parent = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        parent[i] = i;

    // mark 0 and firstPerson as connected from start
    unite(0, firstPerson);

    int idx = 0;
    while (idx < total) {
        int t = all[idx][2];

        // collect meetings at time t
        int start = idx;
        while (idx < total && all[idx][2] == t) idx++;

        // unify all pairs at this time
        for (int i = start; i < idx; i++) {
            int x = all[i][0];
            int y = all[i][1];
            unite(x, y);
        }

        // now reset those who are NOT connected to 0
        for (int i = start; i < idx; i++) {
            int x = all[i][0];
            int y = all[i][1];
            if (findp(x) != findp(0))
                parent[x] = x;
            if (findp(y) != findp(0))
                parent[y] = y;
        }
    }

    // gather result
    int *res = malloc(sizeof(int) * n);
    *returnSize = 0;
    for (int i = 0; i < n; i++) {
        if (findp(i) == findp(0)) {
            res[(*returnSize)++] = i;
        }
    }

    return res;
}
