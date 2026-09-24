#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* exclusiveTime(int n, char** logs, int logsSize, int* returnSize) {
    int* result = (int*)calloc(n, sizeof(int));
    *returnSize = n;

    int stack[logsSize];   // stack to store function ids
    int top = -1;
    int prevTime = 0;

    for (int i = 0; i < logsSize; i++) {
        int id, time;
        char type[6];

        // parse log: "id:start:time" or "id:end:time"
        sscanf(logs[i], "%d:%[^:]:%d", &id, type, &time);

        if (strcmp(type, "start") == 0) {
            if (top != -1) {
                result[stack[top]] += time - prevTime;
            }
            stack[++top] = id;
            prevTime = time;
        } else { // "end"
            result[stack[top]] += time - prevTime + 1;
            top--;
            prevTime = time + 1;
        }
    }

    return result;
}
