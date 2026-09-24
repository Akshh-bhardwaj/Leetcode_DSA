/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct {
    char *code;
    int order;
} Coupon;

int getOrder(char *b) {
    if (strcmp(b, "electronics") == 0) return 0;
    if (strcmp(b, "grocery") == 0) return 1;
    if (strcmp(b, "pharmacy") == 0) return 2;
    if (strcmp(b, "restaurant") == 0) return 3;
    return -1;
}

bool validCode(char *s) {
    if (s == NULL || strlen(s) == 0) return false;
    for (int i = 0; s[i]; i++) {
        if (!(isalnum(s[i]) || s[i] == '_'))
            return false;
    }
    return true;
}

int cmp(const void *a, const void *b) {
    Coupon *x = (Coupon *)a;
    Coupon *y = (Coupon *)b;
    if (x->order != y->order)
        return x->order - y->order;
    return strcmp(x->code, y->code);
}

char** validateCoupons(
    char** code, int codeSize,
    char** businessLine, int businessLineSize,
    bool* isActive, int isActiveSize,
    int* returnSize
) {
    Coupon temp[1000];
    int cnt = 0;

    for (int i = 0; i < codeSize; i++) {
        if (!isActive[i]) continue;

        int ord = getOrder(businessLine[i]);
        if (ord == -1) continue;

        if (!validCode(code[i])) continue;

        temp[cnt].code = code[i];
        temp[cnt].order = ord;
        cnt++;
    }

    qsort(temp, cnt, sizeof(Coupon), cmp);

    char **ans = (char **)malloc(sizeof(char *) * cnt);
    for (int i = 0; i < cnt; i++) {
        ans[i] = temp[i].code;   // ✅ FIX HERE
    }

    *returnSize = cnt;
    return ans;
}
