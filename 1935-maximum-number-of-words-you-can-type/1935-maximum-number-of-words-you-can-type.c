#include <stdio.h>
#include <stdbool.h>

int canBeTypedWords(char * text, char * brokenLetters){
    bool broken[256] = {false};
    // mark broken letters
    for (char *p = brokenLetters; *p; ++p) broken[(unsigned char)*p] = true;

    int count = 0;
    char *p = text;

    while (*p) {
        bool ok = true;
        // scan one word
        while (*p && *p != ' ') {
            if (broken[(unsigned char)*p]) ok = false;
            ++p;
        }
        if (ok) ++count;
        // skip space (if any)
        if (*p == ' ') ++p;
    }

    return count;
}
