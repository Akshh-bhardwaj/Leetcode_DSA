typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} Node;

int reverseNum(int num) {
    int rev = 0;
    while (num > 0) {
        rev = rev * 10 + num % 10;
        num /= 10;
    }
    return rev;
}

int minMirrorPairDistance(int* nums, int numsSize) {
    Node* map = NULL;
    int mini = INT_MAX;

    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];

        Node* found;
        HASH_FIND_INT(map, &num, found);

        if (found) {
            int dist = i - found->val;
            if (dist < mini) mini = dist;
        }

        int rev = reverseNum(num);

        Node* node;
        HASH_FIND_INT(map, &rev, node);
        if (!node) {
            node = malloc(sizeof(Node));
            node->key = rev;
            HASH_ADD_INT(map, key, node);
        }
        node->val = i;
    }

    return mini == INT_MAX ? -1 : mini;
}