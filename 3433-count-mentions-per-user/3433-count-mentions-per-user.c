#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 *
 * Signature (as you provided earlier):
 * int* countMentions(int numberOfUsers, char*** events, int eventsSize, int* eventsColSize, int* returnSize)
 */

static char*** G_EVENTS; // for qsort comparator
static int G_EVENTS_SIZE;

static int event_type_order(const char *type) {
    // OFFLINE must be processed before MESSAGE at same timestamp
    if (strcmp(type, "OFFLINE") == 0) return 0;
    // keep other types (MESSAGE) after
    return 1;
}

static int cmp_idx(const void *a, const void *b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    // timestamps are strings in events[...][1]
    int ta = atoi(G_EVENTS[ia][1]);
    int tb = atoi(G_EVENTS[ib][1]);
    if (ta != tb) return (ta < tb) ? -1 : 1;
    // tie-break: OFFLINE before MESSAGE
    int oa = event_type_order(G_EVENTS[ia][0]);
    int ob = event_type_order(G_EVENTS[ib][0]);
    if (oa != ob) return (oa < ob) ? -1 : 1;
    // otherwise preserve original order
    return ia - ib;
}

int* countMentions(int numberOfUsers, char*** events, int eventsSize, int* eventsColSize, int* returnSize) {
    // result array
    int *ans = (int*)calloc(numberOfUsers, sizeof(int));
    if (!ans) return NULL;

    // prepare index array and global pointer for comparator
    int *idx = (int*)malloc(sizeof(int) * eventsSize);
    if (!idx) { free(ans); return NULL; }
    for (int i = 0; i < eventsSize; ++i) idx[i] = i;
    G_EVENTS = events;
    G_EVENTS_SIZE = eventsSize;

    // sort indices by timestamp, with OFFLINE before MESSAGE at same time
    qsort(idx, eventsSize, sizeof(int), cmp_idx);

    // track last offline start time for each user (initialize to -1e9 -> online)
    // we will store offline_start_time, user is offline when (time - offline_start_time) < 60
    int INF_NEG = -1000000000;
    int *lastOffline = (int*)malloc(sizeof(int) * numberOfUsers);
    if (!lastOffline) { free(ans); free(idx); return NULL; }
    for (int i = 0; i < numberOfUsers; ++i) lastOffline[i] = INF_NEG;

    // process events in sorted order
    for (int p = 0; p < eventsSize; ++p) {
        int i = idx[p];
        char *type = events[i][0];
        int time = atoi(events[i][1]);
        char *body = events[i][2];

        if (strcmp(type, "OFFLINE") == 0) {
            // body is user id (string)
            int uid = atoi(body);
            if (uid >= 0 && uid < numberOfUsers) {
                lastOffline[uid] = time;
            }
        } else { // MESSAGE (and any other message-like types)
            // message body can be:
            //  - "ALL"
            //  - "HERE"
            //  - tokens like "idX" (space separated), duplicates allowed
            if (strcmp(body, "ALL") == 0) {
                for (int u = 0; u < numberOfUsers; ++u) ans[u]++;
            } else if (strcmp(body, "HERE") == 0) {
                for (int u = 0; u < numberOfUsers; ++u) {
                    // user u is online at time iff time - lastOffline[u] >= 60
                    if (time - lastOffline[u] >= 60) ans[u]++;
                }
            } else {
                // parse tokens separated by spaces, count every token that starts with "id" and digits
                int j = 0;
                int L = strlen(body);
                while (j < L) {
                    // skip spaces
                    while (j < L && body[j] == ' ') j++;
                    if (j >= L) break;
                    // token start at j
                    if (body[j] == 'i' && j + 1 < L && body[j+1] == 'd') {
                        j += 2;
                        // parse number
                        int num = 0;
                        int found = 0;
                        while (j < L && isdigit((unsigned char)body[j])) {
                            found = 1;
                            num = num * 10 + (body[j] - '0');
                            j++;
                        }
                        if (found && num >= 0 && num < numberOfUsers) {
                            ans[num]++;
                        }
                    } else {
                        // skip this token (non-id)
                        while (j < L && body[j] != ' ') j++;
                    }
                }
            }
        }
    }

    free(idx);
    free(lastOffline);

    *returnSize = numberOfUsers;
    return ans;
}
