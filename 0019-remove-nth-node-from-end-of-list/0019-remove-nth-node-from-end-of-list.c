struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode *fast = &dummy, *slow = &dummy;

    for (int i = 0; i < n + 1; ++i)
        fast = fast->next;

    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }

    struct ListNode* to_delete = slow->next;
    slow->next = to_delete->next;
    free(to_delete);
    return dummy.next;
}
