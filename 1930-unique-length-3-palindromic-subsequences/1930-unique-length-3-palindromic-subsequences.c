int countPalindromicSubsequence(char * s){
    int n = strlen(s);
    int first[26], last[26];

    // Initialize first and last arrays
    for(int i = 0; i < 26; i++){
        first[i] = n;
        last[i] = -1;
    }

    // Record first and last occurrence of each character
    for(int i = 0; i < n; i++){
        int c = s[i] - 'a';
        if(first[c] == n) first[c] = i;
        last[c] = i;
    }

    int count = 0;

    // For each character as the outer letters of palindrome (a?a)
    for(int c = 0; c < 26; c++){
        if(first[c] < last[c]){  
            // Track which middle characters exist between them
            int seen[26] = {0};
            for(int i = first[c] + 1; i < last[c]; i++){
                seen[s[i] - 'a'] = 1;
            }
            // Count unique middle characters
            for(int j = 0; j < 26; j++){
                if(seen[j]) count++;
            }
        }
    }
    return count;
}