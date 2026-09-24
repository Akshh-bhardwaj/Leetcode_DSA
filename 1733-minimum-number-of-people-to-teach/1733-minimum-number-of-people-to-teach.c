#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Compare two integers (for qsort)
int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Check if two people share a common language
bool canCommunicate(int* person1, int size1, int* person2, int size2) {
    int i = 0, j = 0;
    while (i < size1 && j < size2) {
        if (person1[i] == person2[j]) return true;
        if (person1[i] < person2[j]) i++;
        else j++;
    }
    return false;
}

int minimumTeachings(
    int n,
    int** languages,
    int languagesSize,
    int* languagesColSize,
    int** friendships,
    int friendshipsSize,
    int* friendshipsColSize
) {
    bool* needTeach = (bool*)calloc(languagesSize + 1, sizeof(bool));

    // Step 1: Find all users who cannot communicate
    for (int f = 0; f < friendshipsSize; f++) {
        int u = friendships[f][0] - 1;
        int v = friendships[f][1] - 1;

        qsort(languages[u], languagesColSize[u], sizeof(int), cmp);
        qsort(languages[v], languagesColSize[v], sizeof(int), cmp);

        if (!canCommunicate(languages[u], languagesColSize[u], languages[v], languagesColSize[v])) {
            needTeach[u + 1] = true;
            needTeach[v + 1] = true;
        }
    }

    // Step 2: Count frequency of each language among "needTeach" people
    int* freq = (int*)calloc(n + 1, sizeof(int));
    for (int i = 1; i <= languagesSize; i++) {
        if (needTeach[i]) {
            int idx = i - 1;
            for (int j = 0; j < languagesColSize[idx]; j++) {
                freq[languages[idx][j]]++;
            }
        }
    }

    // Step 3: Find the most known language among them
    int maxKnown = 0;
    for (int i = 1; i <= n; i++) {
        if (freq[i] > maxKnown) maxKnown = freq[i];
    }

    // Step 4: Count how many people need teaching
    int totalNeedTeach = 0;
    for (int i = 1; i <= languagesSize; i++) {
        if (needTeach[i]) totalNeedTeach++;
    }

    free(needTeach);
    free(freq);

    return totalNeedTeach - maxKnown;
}
