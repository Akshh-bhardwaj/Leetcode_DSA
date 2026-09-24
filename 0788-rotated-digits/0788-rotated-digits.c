int rotatedDigits(int n) {
    int count = 0;
    for(int i = 1 ; i <= n ; i++){
        bool valid = true;
        bool changed = false;
        int temp = i;
        while(temp){
            int last_digit = temp%10;
            if(last_digit == 3 || last_digit == 4 ||
             last_digit == 7) 
            valid = false;
            if(last_digit==2 || last_digit == 5 ||
             last_digit == 6 || last_digit == 9)
             changed = true;
             temp /= 10;
        }
        if(valid && changed) count++;
    }
    return count;
}