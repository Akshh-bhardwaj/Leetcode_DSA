long long maxRunTime(int n, int* batteries, int batteriesSize) {
    long long sum = 0;
    for (int i = 0; i < batteriesSize; i++)
        sum += batteries[i];

    long long left = 0;
    long long right = sum / n;  // maximum possible running time

    while (left < right) {
        long long mid = (left + right + 1) / 2;

        long long power = 0;
        for (int i = 0; i < batteriesSize; i++)
            power += batteries[i] < mid ? batteries[i] : mid;

        if (power >= mid * n)
            left = mid;
        else
            right = mid - 1;
    }

    return left;
}
