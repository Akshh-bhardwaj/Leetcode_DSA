char ans[17];

char* findDifferentBinaryString(char** nums, int n) {
    for (int i = 0; i < n; i++) {
        ans[i] = nums[i][i] == '0' ? '1' : '0';
    }
    ans[n] = '\0';
    return ans;
}