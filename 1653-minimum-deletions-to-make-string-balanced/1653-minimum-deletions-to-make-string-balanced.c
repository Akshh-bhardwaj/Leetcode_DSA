int minimumDeletions(char * s){
    int countB = 0;
    int deletions = 0;
    
    for(int i = 0; s[i] != '\0'; i++){
        if(s[i] == 'b'){
            countB++;
        } else {
            deletions = (deletions + 1 < countB) ? deletions + 1 : countB;
        }
    }
    return deletions;
}
