int numberOfSpecialChars(char* word) {
    bool lower[26] = {false};
    bool upper[26] = {false};
    for (int i = 0; word[i] != '\0'; i++) {
        char c = word[i];
        if (c >= 'a' && c <= 'z') {
            lower[c - 'a'] = true;
        } else if (c >= 'A' && c <= 'Z') {
            upper[c - 'A'] = true;
        }
    }
    int ans = 0;
    for (int i = 0; i < 26; i++) {
        if (lower[i] && upper[i]) {
            ans++;
        }
    }
    return ans;
}