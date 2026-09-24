#include <stdio.h>

int countCollisions(char* directions) {
    int n = 0;
    while (directions[n] != '\0') n++;

    int l = 0;
    while (l < n && directions[l] == 'L') {
        l++;
    }

    int r = n - 1;
    while (r >= 0 && directions[r] == 'R') {
        r--;
    }

    int collisions = 0;
    for (int i = l; i <= r; i++) {
        if (directions[i] != 'S') {
            collisions++;
        }
    }
    return collisions;
}