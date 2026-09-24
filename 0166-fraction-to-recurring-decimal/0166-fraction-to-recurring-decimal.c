#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define HASH_SIZE 10007  // prime for hash table size

typedef struct Node {
    long long remainder;
    int index;
    struct Node* next;
} Node;

int hashFunc(long long key) {
    return (int)(key % HASH_SIZE);
}

void insert(Node** table, long long remainder, int index) {
    int hash = hashFunc(remainder);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->remainder = remainder;
    newNode->index = index;
    newNode->next = table[hash];
    table[hash] = newNode;
}

int find(Node** table, long long remainder) {
    int hash = hashFunc(remainder);
    Node* cur = table[hash];
    while (cur) {
        if (cur->remainder == remainder) return cur->index;
        cur = cur->next;
    }
    return -1;
}

char* fractionToDecimal(int numerator, int denominator) {
    if (numerator == 0) {
        char* res = (char*)malloc(2);
        strcpy(res, "0");
        return res;
    }

    char* result = (char*)malloc(10000);
    int idx = 0;

    // Handle sign
    if ((numerator < 0) ^ (denominator < 0)) {
        result[idx++] = '-';
    }

    long long n = llabs((long long)numerator);
    long long d = llabs((long long)denominator);

    // Integer part
    long long integerPart = n / d;
    idx += sprintf(result + idx, "%lld", integerPart);

    long long remainder = n % d;
    if (remainder == 0) {
        result[idx] = '\0';
        return result;
    }

    result[idx++] = '.';

    // Hash table for remainder -> index
    Node* table[HASH_SIZE] = {0};

    while (remainder != 0) {
        int pos = find(table, remainder);
        if (pos != -1) {
            // Insert '('
            for (int j = idx; j >= pos; j--) {
                result[j + 1] = result[j];
            }
            result[pos] = '(';
            idx++;
            result[idx++] = ')';
            result[idx] = '\0';
            return result;
        }

        insert(table, remainder, idx);

        remainder *= 10;
        result[idx++] = (remainder / d) + '0';
        remainder %= d;
    }

    result[idx] = '\0';
    return result;
}
