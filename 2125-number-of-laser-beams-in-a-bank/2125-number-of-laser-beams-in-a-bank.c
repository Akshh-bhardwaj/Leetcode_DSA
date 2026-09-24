#include <stdlib.h>
#include <string.h>

/*
 LeetCode function signature:
 int numberOfBeams(char ** bank, int bankSize)
 
 Idea:
 - For each row, count how many '1's (devices) it has.
 - If the row has >0 devices and there's a previous row with >0 devices,
   add prev_count * curr_count to the answer.
 - Update prev_count when current row has >0 devices.
 
 Time: O(m * n) where m = bankSize, n = length of each row
 Space: O(1)
*/

int numberOfBeams(char **bank, int bankSize) {
    int prev = 0;   // number of devices in last non-empty row
    int ans = 0;

    for (int i = 0; i < bankSize; ++i) {
        int cnt = 0;
        for (int j = 0; bank[i][j] != '\0'; ++j) {
            if (bank[i][j] == '1') ++cnt;
        }
        if (cnt > 0) {
            ans += prev * cnt;
            prev = cnt;
        }
    }

    return ans;
}
