struct ListNode* rotateRight(struct ListNode* head, int k) {
    if (head == NULL)
        return head;

    int node_count = 1;
    struct ListNode* curr = head;
    while (curr->next) {
        curr = curr->next;
        node_count++;
    }

    k %= node_count;
    if (k == 0)
        return head;

    curr->next = head;
    int second_half_count = node_count - k;
    while (second_half_count--) {
        curr = curr->next;
    }
    head = curr->next;
    curr->next = NULL;

    return head;
}