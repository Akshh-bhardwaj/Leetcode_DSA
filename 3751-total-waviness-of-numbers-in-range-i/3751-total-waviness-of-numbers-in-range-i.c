int totalWaviness(int num1, int num2) {
    int total = 0;
    char n[12]; 

    for (int num = num1; num <= num2; ++num) {
        sprintf(n, "%d", num);
        int len = strlen(n);
        if (len < 3) 
            continue;
        
        for (int i = 1; i < len - 1; ++i) {
            if ((n[i] > n[i - 1] && n[i] > n[i + 1]) || 
                (n[i] < n[i - 1] && n[i] < n[i + 1])) {
                total++;
            }
        }
    }
    return total;
}