#include <string.h>
#include <stdbool.h>

bool rotateString(char* s, char* goal) {
    int len = strlen(s);
    if (len != strlen(goal)) return false;
    char temp[len * 2 + 1];
    strcpy(temp, s);
    strcat(temp, s);
    return strstr(temp, goal) != NULL;
}