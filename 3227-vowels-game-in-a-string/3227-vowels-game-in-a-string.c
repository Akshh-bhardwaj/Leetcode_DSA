#include <stdbool.h>
#include <string.h>

bool isVowel(char c) {
    // assuming lowercase input; if uppercase also possible, add those as well
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

bool doesAliceWin(char * s) {
    int n = strlen(s);
    for (int i = 0; i < n; i++) {
        if (isVowel(s[i])) {
            // As soon as we see any vowel, Alice wins per optimal play reasoning
            return true;
        }
    }
    // If no vowel found, Alice cannot make a move and loses
    return false;
}
