#include <stdio.h>
#include <string.h>

int count = 0;
char res[11] = "";  // Max length n = 10

void backtrack(int n, int k, char sb[], int len, char lastChar) {
    if (len == n) {
        count++;
        if (count == k) {
            sb[len] = '\0';
            strcpy(res, sb);
        }
        return;
    }

    char chars[] = {'a', 'b', 'c'};
    for (int i = 0; i < 3; i++) {
        char c = chars[i];
        if (c != lastChar) {
            sb[len] = c;
            backtrack(n, k, sb, len + 1, c);
            if (res[0] != '\0') return; // Early exit
        }
    }
}

char* getHappyString(int n, int k) {
    count = 0;
    res[0] = '\0';  // Reset result
    char sb[11] = "";
    backtrack(n, k, sb, 0, ' ');
    return res;
}