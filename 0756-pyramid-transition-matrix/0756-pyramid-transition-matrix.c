#include <stdbool.h>
#include <string.h>

bool allow[26][26][26];

/* forward declarations */
bool dfs(char *cur, int len);
bool buildRow(char *cur, int len, int idx, char *next);

bool dfs(char *cur, int len) {
    if (len == 1) return true;

    char next[8];
    return buildRow(cur, len, 0, next);
}

bool buildRow(char *cur, int len, int idx, char *next) {
    if (idx == len - 1) {
        next[len - 1] = '\0';
        return dfs(next, len - 1);
    }

    int a = cur[idx] - 'A';
    int b = cur[idx + 1] - 'A';

    for (int c = 0; c < 26; c++) {
        if (allow[a][b][c]) {
            next[idx] = c + 'A';
            if (buildRow(cur, len, idx + 1, next))
                return true;
        }
    }
    return false;
}

bool pyramidTransition(char *bottom, char **allowed, int allowedSize) {
    memset(allow, false, sizeof(allow));

    for (int i = 0; i < allowedSize; i++) {
        allow[allowed[i][0] - 'A']
             [allowed[i][1] - 'A']
             [allowed[i][2] - 'A'] = true;
    }

    return dfs(bottom, strlen(bottom));
}