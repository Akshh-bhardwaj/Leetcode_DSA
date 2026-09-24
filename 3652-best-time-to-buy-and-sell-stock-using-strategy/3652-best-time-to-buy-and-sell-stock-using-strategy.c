#include <stdio.h>
#include <stdlib.h>

// Helper to get maximum of two long long ints
long long maxll(long long a, long long b) {
    return (a > b) ? a : b;
}

long long maxProfit(int* prices, int pricesSize, int* strategy, int strategySize, int k){
    long long originalProfit = 0;
    // 1) Compute original profit
    for(int i = 0; i < pricesSize; i++){
        originalProfit += (long long)strategy[i] * prices[i];
    }

    // Prefix sums for original profit and prices
    long long *s = (long long*)malloc((pricesSize + 1) * sizeof(long long));
    long long *t = (long long*)malloc((pricesSize + 1) * sizeof(long long));

    s[0] = 0;
    t[0] = 0;
    for(int i = 0; i < pricesSize; i++){
        s[i + 1] = s[i] + (long long)strategy[i] * prices[i];
        t[i + 1] = t[i] + prices[i];
    }

    long long answer = originalProfit;
    int half = k / 2;

    // 2) Slide over all windows of size k
    for(int end = k; end <= pricesSize; end++){
        int start = end - k;
        // Profit change if we modify strategy in this segment
        long long delta = - (s[end] - s[start]) 
                          + (t[end] - t[start + half]);
        answer = maxll(answer, originalProfit + delta);
    }

    free(s);
    free(t);
    return answer;
}
