#include <stdlib.h>

int cmp_desc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

long long maximumHappinessSum(int* happiness, int happinessSize, int k) {
    // Sort in descending order
    qsort(happiness, happinessSize, sizeof(int), cmp_desc);

    long long total = 0;
    for (int i = 0; i < k && i < happinessSize; i++) {
        long long value = (long long)happiness[i] - i;
        if (value > 0) {
            total += value;
        } else {
            break;  // no benefit selecting further if becomes zero
        }
    }
    return total;
}
