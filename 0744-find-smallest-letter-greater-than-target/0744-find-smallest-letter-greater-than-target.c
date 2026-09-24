char nextGreatestLetter(char* letters, int lettersSize, char target){
    int left = 0, right = lettersSize - 1;
    char ans = letters[0]; // default wrap-around if nothing is greater

    while (left <= right) {
        int mid = (left + right) / 2;
        if (letters[mid] > target) {
            ans = letters[mid];
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return ans;
}
