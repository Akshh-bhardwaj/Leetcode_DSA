int minOperations(char* s) {
    int diff = 0;
    int n = strlen(s);

    for (int i = 0; i < n; i++) {
        char ex = (i % 2 == 0) ? '1' : '0';
        if (s[i] != ex)
            diff++;
    }

    return (diff < n - diff) ? diff : n - diff;
}