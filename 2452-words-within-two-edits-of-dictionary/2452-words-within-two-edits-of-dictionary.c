/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** twoEditWords(char** queries, int queriesSize, char** dictionary, int dictionarySize, int* returnSize) {
    int word_len = strlen(queries[0]);
    char** res = (char**)malloc(queriesSize * sizeof(char*));
    int count = 0;

    for (int i = 0; i < queriesSize; i++) {
        char* q = queries[i];
        for (int k = 0; k < dictionarySize; k++) {
            char* d = dictionary[k];
            int diff = 0;
            for (int j = 0; j < word_len; j++) {
                if (q[j] != d[j]) 
                    diff++;
                if (diff > 2) 
                    break;
            }
            if (diff <= 2) {
                res[count++] = q;
                break;
            }
        }
    }
    *returnSize = count;
    return res;
}