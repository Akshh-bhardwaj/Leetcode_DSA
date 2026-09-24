#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_SIZE 200003  // large prime for hash table

typedef struct Node {
    char *key;
    char *value;
    struct Node *next;
} Node;

Node* table1[HASH_SIZE]; // exact words
Node* table2[HASH_SIZE]; // lowercase -> first-occurrence original
Node* table3[HASH_SIZE]; // devowel -> first-occurrence original

unsigned long hash(const char *s) {
    unsigned long h = 5381;
    int c;
    while ((c = *s++)) {
        h = ((h << 5) + h) + (unsigned char)c;
    }
    return h % HASH_SIZE;
}

char *strdup_custom(const char *s) {
    size_t n = strlen(s) + 1;
    char *p = (char*)malloc(n);
    if (p) memcpy(p, s, n);
    return p;
}

/* Free all nodes in a table and set buckets to NULL */
void clear_table(Node **table) {
    for (unsigned long i = 0; i < HASH_SIZE; ++i) {
        Node *cur = table[i];
        while (cur) {
            Node *nx = cur->next;
            if (cur->key) free(cur->key);
            if (cur->value) free(cur->value);
            free(cur);
            cur = nx;
        }
        table[i] = NULL;
    }
}

/* Clear all three global tables */
void clear_tables_all() {
    clear_table(table1);
    clear_table(table2);
    clear_table(table3);
}

/* Insert key->value only if key not already present (keeps first occurrence) */
void insert_if_absent(Node **table, const char *key, const char *value) {
    unsigned long h = hash(key);
    Node *cur = table[h];
    while (cur) {
        if (strcmp(cur->key, key) == 0) return; // already exists -> keep first
        cur = cur->next;
    }
    Node *node = (Node*)malloc(sizeof(Node));
    node->key = strdup_custom(key);
    node->value = strdup_custom(value);
    node->next = table[h];
    table[h] = node;
}

char* find_in_table(Node **table, const char *key) {
    unsigned long h = hash(key);
    Node *cur = table[h];
    while (cur) {
        if (strcmp(cur->key, key) == 0) return cur->value;
        cur = cur->next;
    }
    return NULL;
}

int is_vowel(char c) {
    c = tolower((unsigned char)c);
    return c=='a'||c=='e'||c=='i'||c=='o'||c=='u';
}

char *lower_copy(const char *s) {
    int n = strlen(s);
    char *t = (char*)malloc(n+1);
    for (int i=0;i<n;i++) t[i] = tolower((unsigned char)s[i]);
    t[n] = '\0';
    return t;
}

char *devowel_copy(const char *s) {
    int n = strlen(s);
    char *t = (char*)malloc(n+1);
    for (int i=0;i<n;i++) {
        char c = tolower((unsigned char)s[i]);
        t[i] = is_vowel(c) ? '*' : c;
    }
    t[n] = '\0';
    return t;
}

/**
 * LeetCode API:
 * char **spellchecker(char **wordlist, int wordlistSize, char **queries, int queriesSize, int* returnSize)
 */
char **spellchecker(char **wordlist, int wordlistSize, char **queries, int queriesSize, int* returnSize){
    /* Clear previous runs' data to avoid interference across multiple testcases */
    clear_tables_all();

    /* Build hash tables using first occurrence semantics */
    for (int i=0;i<wordlistSize;i++) {
        char *w = wordlist[i];
        /* exact words: map exact->exact (we can keep first occurrence but duplicates don't matter) */
        insert_if_absent(table1, w, w);

        /* case-insensitive: map lowercase -> original (first occurrence) */
        char *low = lower_copy(w);
        insert_if_absent(table2, low, w);
        free(low);

        /* devowelized: map devowel(lowercase) -> original (first occurrence) */
        char *dev = devowel_copy(w);
        insert_if_absent(table3, dev, w);
        free(dev);
    }

    char **ans = (char**)malloc(sizeof(char*) * queriesSize);
    *returnSize = queriesSize;

    for (int q=0;q<queriesSize;q++) {
        char *query = queries[q];
        char *res = NULL;

        /* 1) exact match */
        res = find_in_table(table1, query);
        if (res) {
            ans[q] = strdup_custom(res);
            continue;
        }

        /* 2) case-insensitive match */
        char *lowq = lower_copy(query);
        res = find_in_table(table2, lowq);
        if (res) {
            ans[q] = strdup_custom(res);
            free(lowq);
            continue;
        }

        /* 3) vowel-error match */
        char *devq = devowel_copy(query);
        res = find_in_table(table3, devq);
        if (res) ans[q] = strdup_custom(res);
        else ans[q] = strdup_custom("");

        free(lowq);
        free(devq);
    }

    /* optional: keep tables around for the duration of this process, but they are cleared at next call */
    return ans;
}
