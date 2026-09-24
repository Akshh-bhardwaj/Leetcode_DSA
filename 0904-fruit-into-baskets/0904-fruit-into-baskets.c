int totalFruit(int* fruits, int fruitsSize){
    if (fruitsSize == 0) return 0;
    int a = -1, b = -1;          // the two fruit types (b is the most recent)
    int count_b = 0;             // consecutive count of fruit type b at the window's tail
    int curr_window = 0;
    int res = 0;
    
    for (int i = 0; i < fruitsSize; ++i) {
        int f = fruits[i];
        if (f == a || f == b) {
            // still within two types
            curr_window++;
        } else {
            // new third type: shrink window to keep tail streak of b plus current
            curr_window = count_b + 1;
        }
        
        if (f == b) {
            // extend consecutive b run
            count_b++;
        } else {
            // shift: previous b becomes a, new fruit becomes b
            count_b = 1;
            a = b;
            b = f;
        }
        
        if (curr_window > res) res = curr_window;
    }
    return res;
}
