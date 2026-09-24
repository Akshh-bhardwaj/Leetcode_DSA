

#include <string.h>

int longestBalanced(char * s){
    int n = strlen(s);
    int ans = 0;

    for(int i = 0; i < n; i++){
        int freq[26] = {0};

        for(int j = i; j < n; j++){
            freq[s[j] - 'a']++;

            int count = 0, common = -1;
            bool ok = true;

            for(int k = 0; k < 26; k++){
                if(freq[k] > 0){
                    if(common == -1) common = freq[k];
                    else if(freq[k] != common){
                        ok = false;
                        break;
                    }
                    count++;
                }
            }

            if(ok && count > 0){
                int len = j - i + 1;
                if(len > ans) ans = len;
            }
        }
    }

    return ans;
}
