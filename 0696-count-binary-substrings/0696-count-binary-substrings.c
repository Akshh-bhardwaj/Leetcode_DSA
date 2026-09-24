int countBinarySubstrings(char *s) {
    int prev = 0;
    int curr = 1;
    int res = 0;

    for (int i = 1; s[i] != '\0'; i++) {
        if (s[i] == s[i-1]) {
            curr++;
        } else {
            res += prev < curr ? prev : curr;
            prev = curr;
            curr = 1;
        }
    }

    res += prev < curr ? prev : curr;
    return res;
}
