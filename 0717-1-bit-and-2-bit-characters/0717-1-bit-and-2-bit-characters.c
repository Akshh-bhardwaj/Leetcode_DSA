#include <stdbool.h>

bool isOneBitCharacter(int* bits, int bitsSize) {
    int i = 0;
    // iterate until the last index or before it
    while (i < bitsSize - 1) {
        if (bits[i] == 1) {
            // '1' starts a 2-bit character, skip the next bit
            i += 2;
        } else {
            // '0' is a 1-bit character
            i += 1;
        }
    }
    // if we land exactly on the last index, it's a 1-bit character
    return i == bitsSize - 1;
}