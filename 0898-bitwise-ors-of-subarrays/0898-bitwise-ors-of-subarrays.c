#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_OR_RESULT 1000000  // estimate, safely under 1 million
#define MAX_CUR 128            // max ORs per index

// Simple hash set with linear probing for int
typedef struct {
    int* data;
    bool* used;
    int size;
    int capacity;
} HashSet;

HashSet* createSet(int capacity) {
    HashSet* set = malloc(sizeof(HashSet));
    set->data = malloc(sizeof(int) * capacity);
    set->used = calloc(capacity, sizeof(bool));
    set->size = 0;
    set->capacity = capacity;
    return set;
}

void freeSet(HashSet* set) {
    free(set->data);
    free(set->used);
    free(set);
}

int hash(int x, int mod) {
    return ((x % mod) + mod) % mod;
}

bool setContains(HashSet* set, int val) {
    int i = hash(val, set->capacity);
    int start = i;
    while (set->used[i]) {
        if (set->data[i] == val) return true;
        i = (i + 1) % set->capacity;
        if (i == start) break;
    }
    return false;
}

void setInsert(HashSet* set, int val) {
    int i = hash(val, set->capacity);
    while (set->used[i]) {
        if (set->data[i] == val) return;
        i = (i + 1) % set->capacity;
    }
    set->data[i] = val;
    set->used[i] = true;
    set->size++;
}

int subarrayBitwiseORs(int* arr, int arrSize) {
    HashSet* resultSet = createSet(MAX_OR_RESULT);
    HashSet* prev = createSet(MAX_CUR);

    for (int i = 0; i < arrSize; i++) {
        HashSet* curr = createSet(MAX_CUR);

        // Add current element
        setInsert(curr, arr[i]);
        setInsert(resultSet, arr[i]);

        // For all previous ORs
        for (int j = 0; j < prev->capacity; j++) {
            if (prev->used[j]) {
                int val = prev->data[j] | arr[i];
                if (!setContains(curr, val)) {
                    setInsert(curr, val);
                    setInsert(resultSet, val);
                }
            }
        }

        freeSet(prev);
        prev = curr;
    }

    int count = resultSet->size;
    freeSet(prev);
    freeSet(resultSet);
    return count;
}
