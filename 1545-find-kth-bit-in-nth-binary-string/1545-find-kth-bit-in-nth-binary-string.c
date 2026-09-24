char findKthBit(int n, int k) {
    int length = 1 << (n - 1); 
    char ans = '0';
    
    while (k > 1) {
        if (k > length) {
            k = 2 * length - k;
            
            ans = ans == '0' ? '1' : '0';
        }
        
        length >>= 1; 
    }
    
    return ans;
}