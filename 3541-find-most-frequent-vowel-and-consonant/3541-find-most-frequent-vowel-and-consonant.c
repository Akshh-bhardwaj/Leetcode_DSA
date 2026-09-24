#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxFreqSum(char * s) {
    int freq[26] = {0};

    // Count frequency of each letter
    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (c >= 'a' && c <= 'z') {
            freq[c - 'a']++;
        }
    }

    // Vowel lookup
    int isVowel[26] = {0};
    isVowel['a' - 'a'] = 1;
    isVowel['e' - 'a'] = 1;
    isVowel['i' - 'a'] = 1;
    isVowel['o' - 'a'] = 1;
    isVowel['u' - 'a'] = 1;

    int maxVowel = 0, maxConsonant = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] == 0) continue;
        if (isVowel[i]) {
            if (freq[i] > maxVowel) maxVowel = freq[i];
        } else {
            if (freq[i] > maxConsonant) maxConsonant = freq[i];
        }
    }

    return maxVowel + maxConsonant;
}
