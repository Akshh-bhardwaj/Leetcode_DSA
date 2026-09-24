bool hasAlternatingBits(int n){
    int prev = n & 1;   // get least significant bit
    n >>= 1;            // shift right to process next bit

    while(n > 0){
        int curr = n & 1;
        if(curr == prev) return false;
        prev = curr;    // update for next comparison
        n >>= 1;        // shift right
    }

    return true;
}
