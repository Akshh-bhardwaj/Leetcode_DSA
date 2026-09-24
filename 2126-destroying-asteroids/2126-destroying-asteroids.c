int compare(const void *a, const void *b){
    int aa = *(int*) a;
    int bb = *(int*) b;
    return (aa > bb) - (aa < bb);
}
bool asteroidsDestroyed(int mass, int* asteroids, int asteroidsSize) {
    qsort(asteroids,asteroidsSize,sizeof(int),compare);
    long long m = mass;
    for(int i = 0 ; i < asteroidsSize ; i++){
        if(m < asteroids[i])
            return false;
        m += asteroids[i];
    }
    return true;
}