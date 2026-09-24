int lower_bound(long long* arr, int size, long long target) {
    int left = 0, right = size;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return left;
}

int compare(const void* a, const void* b) {
    long long la = *(const long long*)a;
    long long lb = *(const long long*)b;
    return (la > lb) - (la < lb);
}

int check(long long* arr, int size, int side, int k, long long limit) {
    long long perimeter = side * 4LL;

    for (int i = 0; i < size; i++) {
        long long start = arr[i];
        long long end = start + perimeter - limit;
        long long cur = start;

        for (int j = 0; j < k - 1; j++) {
            int idx = lower_bound(arr, size, cur + limit);
            if (idx == size || arr[idx] > end) {
                cur = -1;
                break;
            }
            cur = arr[idx];
        }

        if (cur >= 0) {
            return 1;
        }
    }
    return 0;
}

int maxDistance(int side, int** points, int pointsSize, int* pointsColSize,
                int k) {
    long long* arr = (long long*)malloc(pointsSize * sizeof(long long));

    for (int i = 0; i < pointsSize; i++) {
        int x = points[i][0], y = points[i][1];
        if (x == 0) {
            arr[i] = y;
        } else if (y == side) {
            arr[i] = side + (long long)x;
        } else if (x == side) {
            arr[i] = side * 3LL - y;
        } else {
            arr[i] = side * 4LL - x;
        }
    }

    qsort(arr, pointsSize, sizeof(long long), compare);

    long long lo = 1, hi = side;
    int ans = 0;
    while (lo <= hi) {
        long long mid = (lo + hi) / 2;
        if (check(arr, pointsSize, side, k, mid)) {
            lo = mid + 1;
            ans = (int)mid;
        } else {
            hi = mid - 1;
        }
    }

    free(arr);
    return ans;
}