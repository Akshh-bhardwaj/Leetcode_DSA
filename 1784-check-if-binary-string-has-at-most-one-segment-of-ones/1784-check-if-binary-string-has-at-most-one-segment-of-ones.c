bool checkOnesSegment(char* s) {
    int n=strlen(s);
    if(n==1)return true;
    for(int i=0;i<n-1;i++){
        if(s[i]=='0'&&s[i+1]=='1')
            return false;
    }
    return true;
}