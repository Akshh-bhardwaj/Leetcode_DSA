int cmp(const void* a, const void* b) {
    int* x = *(int**)a;
    int* y = *(int**)b;
    return (y[1] - y[0]) - (x[1] - x[0]);
}

int minimumEffort(int** tasks, int tasksSize, int* tasksColSize) {
    qsort(tasks, tasksSize, sizeof(int*), cmp);
    int need = 0;
    for (int i = tasksSize - 1; i >= 0; i--) {
        int actual = tasks[i][0];
        int minimum = tasks[i][1];
        need = (minimum > need + actual) ? minimum : need + actual;
    }
    return need;
}