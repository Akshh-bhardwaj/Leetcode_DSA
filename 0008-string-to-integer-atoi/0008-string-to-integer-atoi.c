#include <stdio.h>
#include <limits.h>
#include <ctype.h>

int myAtoi(char* s) {
    int i = 0;
    int sign = 1;
    long result = 0;

    // 1. Skip leading whitespaces
    while (isspace(s[i])) {
        i++;
    }

    // 2. Handle sign
    if (s[i] == '+' || s[i] == '-') {
        sign = (s[i] == '-') ? -1 : 1;
        i++;
    }

    // 3. Convert digits
    while (isdigit(s[i])) {
        int digit = s[i] - '0';

        // 4. Overflow check before result update
        if (result > (LONG_MAX - digit) / 10) {
            return (sign == 1) ? INT_MAX : INT_MIN;
        }

        result = result * 10 + digit;
        i++;
    }

    result *= sign;

    // 5. Clamp to 32-bit int range
    if (result > INT_MAX) return INT_MAX;
    if (result < INT_MIN) return INT_MIN;

    return (int)result;
}
