int numberOfSpecialChars(char* word) {

    int count = 0;

    for(char ch = 'a'; ch <= 'z'; ch++) {

        int lastLower = -1;
        int firstUpper = -1;

        for(int i = 0; word[i] != '\0'; i++) {

            if(word[i] == ch)
                lastLower = i;

            if(word[i] == ch - 32 && firstUpper == -1)
                firstUpper = i;
        }

        if(lastLower != -1 &&
           firstUpper != -1 &&
           lastLower < firstUpper) {

            count++;
        }
    }

    return count;
}