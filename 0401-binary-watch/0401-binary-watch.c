/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int countBits(int n){
    int count = 0;
    while(n){
        count += n & 1;
        n >>= 1;
    }
    return count;
}

char ** readBinaryWatch(int turnedOn, int* returnSize){
    char **result = (char**)malloc(720 * sizeof(char*));
    *returnSize = 0;

    for(int h = 0; h < 12; h++){
        for(int m = 0; m < 60; m++){
            if(countBits(h) + countBits(m) == turnedOn){
                result[*returnSize] = (char*)malloc(6 * sizeof(char));
                sprintf(result[*returnSize], "%d:%02d", h, m);
                (*returnSize)++;
            }
        }
    }
    return result;
}