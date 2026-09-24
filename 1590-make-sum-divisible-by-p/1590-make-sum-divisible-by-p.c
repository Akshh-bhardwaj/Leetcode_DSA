#include <stdlib.h>
#include <limits.h>

typedef struct {
    int key;
    int value;
    int used;
} Entry;

int minSubarray(int* nums, int numsSize, int p) {
    long long total = 0;
    for (int i = 0; i < numsSize; i++) total += nums[i];

    int target = total % p;
    if (target == 0) return 0;

    // Build a simple hashmap with open addressing
    int cap = numsSize * 4 + 10;
    Entry* map = (Entry*)malloc(sizeof(Entry) * cap);
    for (int i = 0; i < cap; i++) map[i].used = 0;

    // Helper: insert key → value in hashmap
    #define INSERT(k, v) do { \
        int h = (k) % cap; if (h < 0) h += cap; \
        while (map[h].used && map[h].key != (k)) h = (h + 1) % cap; \
        map[h].key = (k); \
        map[h].value = (v); \
        map[h].used = 1; \
    } while(0)

    // Helper: find value of key, return INT_MIN if not found
    #define FIND(k, out) do { \
        int h = (k) % cap; if (h < 0) h += cap; \
        out = INT_MIN; \
        while (map[h].used) { \
            if (map[h].key == (k)) { out = map[h].value; break; } \
            h = (h + 1) % cap; \
        } \
    } while(0)

    // Insert prefixMod = 0 at index -1
    INSERT(0, -1);

    long long prefix = 0;
    int ans = INT_MAX;

    for (int i = 0; i < numsSize; i++) {
        prefix = (prefix + nums[i]) % p;
        int cur = prefix;

        int need = (cur - target) % p;
        if (need < 0) need += p;

        int found;
        FIND(need, found);

        if (found != INT_MIN) {
            int len = i - found;
            if (len < ans) ans = len;
        }

        INSERT(cur, i);
    }

    free(map);
    return (ans == INT_MAX || ans == numsSize) ? -1 : ans;
}
