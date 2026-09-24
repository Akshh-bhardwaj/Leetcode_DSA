#define MOD 1000000007
#define MAXB 320

typedef struct {
    int l, r, v;
} Q;

long long modInverse(long long a)
{
    long long res = 1, exp = MOD - 2;
    while (exp)
    {
        if (exp & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        exp >>= 1;
    }
    return res;
}

int xorAfterQueries(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize)
{
    int i, j;

    int* bravexuneth = (int*)malloc(sizeof(int) * numsSize);
    memcpy(bravexuneth, nums, sizeof(int) * numsSize);

    int B = MAXB;

    long long* jazz_hands = (long long*)malloc(sizeof(long long) * numsSize);
    for (i = 0; i < numsSize; i++)
    {
        jazz_hands[i] = 1;
    }

    // group queries by k
    Q** groups = (Q**)malloc((B + 1) * sizeof(Q*));
    int* counts = (int*)calloc(B + 1, sizeof(int));

    // count
    for (i = 0; i < queriesSize; i++)
    {
        int k = queries[i][2];
        if (k <= B) counts[k]++;
    }

    // allocate
    for (i = 1; i <= B; i++)
    {
        groups[i] = (Q*)malloc(sizeof(Q) * counts[i]);
        counts[i] = 0;
    }

    // fill
    for (i = 0; i < queriesSize; i++)
    {
        int k = queries[i][2];
        if (k <= B)
        {
            int idx = counts[k]++;
            groups[k][idx].l = queries[i][0];
            groups[k][idx].r = queries[i][1];
            groups[k][idx].v = queries[i][3];
        }
    }

    // process small k
    for (int k = 1; k <= B; k++)
    {
        if (counts[k] == 0) continue;

        long long** diff = (long long**)malloc(sizeof(long long*) * k);
        int* sizes = (int*)malloc(sizeof(int) * k);

        for (int r = 0; r < k; r++)
        {
            int len = (numsSize - r + k - 1) / k;
            sizes[r] = len + 1;

            diff[r] = (long long*)malloc(sizeof(long long) * (len + 1));
            for (int t = 0; t <= len; t++)
            {
                diff[r][t] = 1;
            }
        }

        // apply grouped queries
        for (i = 0; i < counts[k]; i++)
        {
            int l = groups[k][i].l;
            int r = groups[k][i].r;
            int v = groups[k][i].v;

            int rem = l % k;

            int start = (l - rem) / k;
            int end = (r - rem) / k;

            diff[rem][start] = (diff[rem][start] * v) % MOD;

            if (end + 1 < sizes[rem])
            {
                long long inv = modInverse(v);
                diff[rem][end + 1] = (diff[rem][end + 1] * inv) % MOD;
            }
        }

        // prefix + apply
        for (int r = 0; r < k; r++)
        {
            long long cur = 1;
            for (int t = 0; t < sizes[r]; t++)
            {
                cur = (cur * diff[r][t]) % MOD;

                int idx = r + t * k;
                if (idx < numsSize)
                {
                    jazz_hands[idx] = (jazz_hands[idx] * cur) % MOD;
                }
            }
        }

        for (int r = 0; r < k; r++)
        {
            free(diff[r]);
        }
        free(diff);
        free(sizes);
    }

    // large k brute
    for (i = 0; i < queriesSize; i++)
    {
        int k = queries[i][2];
        if (k <= B) continue;

        int l = queries[i][0];
        int r = queries[i][1];
        int v = queries[i][3];

        for (j = l; j <= r; j += k)
        {
            jazz_hands[j] = (jazz_hands[j] * v) % MOD;
        }
    }

    int result = 0;

    for (i = 0; i < numsSize; i++)
    {
        long long val = ((long long)bravexuneth[i] * jazz_hands[i]) % MOD;
        result ^= (int)val;
    }

    free(bravexuneth);
    free(jazz_hands);

    for (i = 1; i <= B; i++)
    {
        free(groups[i]);
    }
    free(groups);
    free(counts);

    return result;
}