#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Check vowel
bool isVowel(char c) {
    return c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||
           c=='A'||c=='E'||c=='I'||c=='O'||c=='U';
}

char* sortVowels(char* s) {
    int n = strlen(s);
    char* result = (char*)malloc((n + 1) * sizeof(char));
    strcpy(result, s);

    // Counting array for vowels (ASCII range 128 is enough)
    int count[128] = {0};

    // Collect frequency of vowels
    for (int i = 0; i < n; i++) {
        if (isVowel(s[i])) {
            count[(int)s[i]]++;
        }
    }

    // Sorted order of vowels (ASCII order)
    char order[] = {'A','E','I','O','U','a','e','i','o','u'};
    int idx = 0;

    // Replace vowels in sorted order
    for (int i = 0; i < n; i++) {
        if (isVowel(result[i])) {
            // Find next available vowel from order[]
            while (count[(int)order[idx]] == 0) {
                idx++;
            }
            result[i] = order[idx];
            count[(int)order[idx]]--;
        }
    }

    return result;
}
