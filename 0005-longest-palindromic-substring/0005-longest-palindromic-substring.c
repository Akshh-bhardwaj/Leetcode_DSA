#include <stdio.h>
#include <string.h>

// Helper function to expand and return length
int expandFromCenter(char* s, int left, int right) {
    while (left >= 0 && right < strlen(s) && s[left] == s[right]) {
        left--;
        right++;
    }
    return right - left - 1;  // Length of palindrome
}

char* longestPalindrome(char* s) {
    int start = 0, end = 0;

    for (int i = 0; i < strlen(s); i++) {
        int len1 = expandFromCenter(s, i, i);     // Odd length
        int len2 = expandFromCenter(s, i, i + 1); // Even length
        int len = (len1 > len2) ? len1 : len2;

        if (len > end - start) {
            start = i - (len - 1) / 2;
            end = i + len / 2;
        }
    }

    // Allocate space for result + null terminator
    int resultLength = end - start + 1;
    char* result = (char*)malloc((resultLength + 1) * sizeof(char));
    strncpy(result, s + start, resultLength);
    result[resultLength] = '\0';

    return result;
}
