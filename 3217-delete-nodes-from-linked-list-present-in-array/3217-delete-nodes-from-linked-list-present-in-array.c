/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

#include <stdlib.h>
#include <stdbool.h>

struct ListNode* modifiedList(int* nums, int numsSize, struct ListNode* head) {
    // Create a hash‐table (via simple array) for lookup of values in nums.
    // Since 1 <= nums[i] <= 10^5 per constraints. :contentReference[oaicite:1]{index=1}
    int maxVal = 100000;
    bool *toRemove = (bool*)calloc((maxVal + 1), sizeof(bool));
    for (int i = 0; i < numsSize; i++) {
        int v = nums[i];
        if (v >= 1 && v <= maxVal) {
            toRemove[v] = true;
        }
    }

    // Use dummy node to simplify handling removal when head itself must be removed.
    struct ListNode dummy;
    dummy.val = 0;
    dummy.next = head;
    struct ListNode* prev = &dummy;

    while (prev->next != NULL) {
        if (toRemove[prev->next->val]) {
            // skip the node
            prev->next = prev->next->next;
        } else {
            prev = prev->next;
        }
    }

    free(toRemove);
    return dummy.next;
}
