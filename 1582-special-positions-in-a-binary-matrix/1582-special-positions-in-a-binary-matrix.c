int numSpecial(int** a, const int m, const int* pn) {
    const int n = pn[0];
    int row[m];
    int col[n];
    for (int j = 0; j < n; ++j) col[j] = 0;
    for (int i = 0; i < m; ++i) {
        row[i] = 0;
        for (int j = 0; j < n; ++j) {
            if (a[i][j] == 1) {
                ++row[i];
                ++col[j];
            }
        }
    }
    int ctr = 0;
    for (int i = 0; i < m; ++i) {
        if (row[i] != 1) continue;
        for (int j = 0; j < n; ++j) {
            if (a[i][j] == 1) {
                ctr += col[j] == 1;
                break;
            }
        }
    }
    return ctr;
}