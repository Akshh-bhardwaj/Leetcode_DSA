#include <stdio.h>
#include <stdlib.h>

/* ---------- Available Rooms Min Heap ---------- */
typedef struct {
    int *a;
    int size;
} RoomHeap;

void roomPush(RoomHeap *h, int x) {
    h->a[h->size] = x;
    int i = h->size++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->a[p] <= h->a[i]) break;
        int t = h->a[p]; h->a[p] = h->a[i]; h->a[i] = t;
        i = p;
    }
}

int roomPop(RoomHeap *h) {
    int r = h->a[0];
    h->a[0] = h->a[--h->size];
    int i = 0;
    while (1) {
        int l = 2*i+1, r2 = 2*i+2, s = i;
        if (l < h->size && h->a[l] < h->a[s]) s = l;
        if (r2 < h->size && h->a[r2] < h->a[s]) s = r2;
        if (s == i) break;
        int t = h->a[i]; h->a[i] = h->a[s]; h->a[s] = t;
        i = s;
    }
    return r;
}

/* ---------- Busy Rooms Min Heap ---------- */
typedef struct {
    long long end;
    int room;
} Busy;

typedef struct {
    Busy *a;
    int size;
} BusyHeap;

void busyPush(BusyHeap *h, long long end, int room) {
    h->a[h->size] = (Busy){end, room};
    int i = h->size++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->a[p].end < h->a[i].end ||
           (h->a[p].end == h->a[i].end && h->a[p].room <= h->a[i].room))
            break;
        Busy t = h->a[p]; h->a[p] = h->a[i]; h->a[i] = t;
        i = p;
    }
}

Busy busyPop(BusyHeap *h) {
    Busy r = h->a[0];
    h->a[0] = h->a[--h->size];
    int i = 0;
    while (1) {
        int l = 2*i+1, r2 = 2*i+2, s = i;
        if (l < h->size &&
           (h->a[l].end < h->a[s].end ||
           (h->a[l].end == h->a[s].end && h->a[l].room < h->a[s].room)))
            s = l;
        if (r2 < h->size &&
           (h->a[r2].end < h->a[s].end ||
           (h->a[r2].end == h->a[s].end && h->a[r2].room < h->a[s].room)))
            s = r2;
        if (s == i) break;
        Busy t = h->a[i]; h->a[i] = h->a[s]; h->a[s] = t;
        i = s;
    }
    return r;
}

/* ---------- Correct Comparator ---------- */
int cmp(const void *a, const void *b) {
    int *m1 = *(int **)a;
    int *m2 = *(int **)b;
    return m1[0] - m2[0];
}

/* ---------- Main Function ---------- */
int mostBooked(int n, int **meetings, int meetingsSize, int *meetingsColSize) {
    qsort(meetings, meetingsSize, sizeof(int *), cmp);

    RoomHeap avail;
    avail.a = malloc(n * sizeof(int));
    avail.size = 0;
    for (int i = 0; i < n; i++) roomPush(&avail, i);

    BusyHeap busy;
    busy.a = malloc(n * sizeof(Busy));
    busy.size = 0;

    int *cnt = calloc(n, sizeof(int));

    for (int i = 0; i < meetingsSize; i++) {
        long long s = meetings[i][0];
        long long e = meetings[i][1];

        while (busy.size && busy.a[0].end <= s) {
            Busy b = busyPop(&busy);
            roomPush(&avail, b.room);
        }

        if (avail.size) {
            int r = roomPop(&avail);
            cnt[r]++;
            busyPush(&busy, e, r);
        } else {
            Busy b = busyPop(&busy);
            long long dur = e - s;
            cnt[b.room]++;
            busyPush(&busy, b.end + dur, b.room);
        }
    }

    int ans = 0;
    for (int i = 1; i < n; i++)
        if (cnt[i] > cnt[ans]) ans = i;

    return ans;
}
