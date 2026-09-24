int furthestDistanceFromOrigin(char* moves) {
    int c=strlen(moves),x=0,cl=0,cr=0;
    for(int i=0;i<c;i++)
    {
        if(moves[i]=='L')cl++;
        else if(moves[i]=='R')cr++;
    }
    for(int i=0;i<c;i++)
    {
        if(cr>cl)
        {
            if(moves[i]=='_') moves[i]='R';
        }
        else
        {
            if(moves[i]=='_') moves[i]='L';
        }
    }
    for(int i=0;i<c;i++)
    {
        if(moves[i]=='L') x--;
        else x++;
    }
    if(x<0) return x-2*x;
    else
    return x;
}