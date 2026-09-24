#include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b){
    return strcmp(*(char**)b, *(char**)a);
}

char* makeLargestSpecial(char* s){
    int n = strlen(s);
    if(n <= 2) return strdup(s);

    char* arr[60];
    int count = 0, start = 0, idx = 0;

    for(int i=0;i<n;i++){
        count += (s[i]=='1') ? 1 : -1;
        if(count==0){
            char temp[60];
            strncpy(temp, s+start+1, i-start-1);
            temp[i-start-1] = '\0';

            char *inner = makeLargestSpecial(temp);

            arr[idx] = malloc(strlen(inner)+3);
            sprintf(arr[idx], "1%s0", inner);
            free(inner);

            idx++;
            start = i+1;
        }
    }

    qsort(arr, idx, sizeof(char*), cmp);

    char *res = malloc(n+1);
    res[0]='\0';
    for(int i=0;i<idx;i++){
        strcat(res, arr[i]);
        free(arr[i]);
    }
    return res;
}