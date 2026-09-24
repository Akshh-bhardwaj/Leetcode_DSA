#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** buildArray(int* target, int targetSize, int n, int* returnSize) {
    char** result = (char**)malloc(2 * n * sizeof(char*));
    int idx = 0;
    int curr = 1;

    for (int i = 0; i < targetSize; i++) {
        while (curr < target[i]) {
            result[idx] = (char*)malloc(5 * sizeof(char)); // "Push" + '\0'
            strcpy(result[idx++], "Push");

            result[idx] = (char*)malloc(4 * sizeof(char)); // "Pop" + '\0'
            strcpy(result[idx++], "Pop");

            curr++;
        }

        result[idx] = (char*)malloc(5 * sizeof(char)); // "Push" + '\0'
        strcpy(result[idx++], "Push");
        curr++;
    }

    *returnSize = idx;
    return result;
}
