int bitwiseComplement(int n) {
    if(n==0)return 1;
        else if(n==1)return 0;
        int n1 = 1;
        while(n1<=n){
            n1*=2;
        }
        return n1-1-n;
}