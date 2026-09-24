int binaryGap(int n) {
    int last = -1;
    int pos = 0;
    int max = 0;

    while (n > 0) {
        if (n & 1) {
            if (last != -1) {
                int gap = pos - last;
                if (gap > max) max = gap;
            }
            last = pos;
        }
        pos++;
        n >>= 1;
    }
    return max;
}