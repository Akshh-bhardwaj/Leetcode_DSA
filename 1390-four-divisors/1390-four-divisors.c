int sumFourDivisors(int* nums, int numsSize) {
    int total = 0;

    for (int i = 0; i < numsSize; i++) {
        int n = nums[i];
        int cnt = 0;
        int sum = 0;

        for (int d = 1; d * d <= n; d++) {
            if (n % d == 0) {
                int e = n / d;

                if (d == e) {
                    cnt++;
                    sum += d;
                } else {
                    cnt += 2;
                    sum += d + e;
                }

                if (cnt > 4) break;
            }
        }

        if (cnt == 4)
            total += sum;
    }

    return total;
}
