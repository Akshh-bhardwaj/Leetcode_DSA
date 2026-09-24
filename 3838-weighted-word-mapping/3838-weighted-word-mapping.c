#pragma optimize("O3, unroll-loops")
char* mapWordWeights(char** words, int n, int* weights, int m) {
    char* ans=(char*)malloc((n+1)*sizeof(char));
    ans[n]='\0';
    for(int i=0; i<n; i++){
        int Sum=0;
        char* w=words[i];
        for(int j=0; w[j]!='\0'; j++) Sum+=weights[w[j]-'a'];
        ans[i]='a'+(25-Sum%26);
    }
    return ans;
}