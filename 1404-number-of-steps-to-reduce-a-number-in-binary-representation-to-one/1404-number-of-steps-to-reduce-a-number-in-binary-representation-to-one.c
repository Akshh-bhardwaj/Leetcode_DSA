int numSteps(char *s) {
    int n = strlen(s);
    int steps = 0;
    int carry = 0;

    // start from last bit → second bit
    for (int i = n - 1; i > 0; i--) {
        int bit = (s[i] - '0') + carry;

        if (bit == 1) {
            steps += 2;   // add 1 then divide
            carry = 1;
        } else {
            steps += 1;   // just divide
        }
    }

    return steps + carry;
}