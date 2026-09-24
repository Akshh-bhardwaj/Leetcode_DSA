int cmp(const void *a, const void *b) {
    int *x = *(int **)a;
    int *y = *(int **)b;
    return x[0] - y[0];
}

int maxTwoEvents(int** events, int eventsSize, int* eventsColSize) {
    // Sort by start time
    qsort(events, eventsSize, sizeof(int*), cmp);

    int *maxValFrom = (int*)malloc(eventsSize * sizeof(int));
    maxValFrom[eventsSize-1] = events[eventsSize-1][2];

    // Build suffix max array
    for (int i = eventsSize - 2; i >= 0; i--) {
        maxValFrom[i] = 
            (maxValFrom[i+1] > events[i][2]) ? maxValFrom[i+1] : events[i][2];
    }

    int answer = 0;

    for (int i = 0; i < eventsSize; i++) {
        int currVal = events[i][2];
        // Single best
        if (currVal > answer) answer = currVal;

        // Binary search for the next non-overlapping event
        int left = i + 1, right = eventsSize;
        while (left < right) {
            int mid = (left + right) / 2;
            if (events[mid][0] > events[i][1]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        if (left < eventsSize) {
            int combined = currVal + maxValFrom[left];
            if (combined > answer) answer = combined;
        }
    }

    free(maxValFrom);
    return answer;
}
