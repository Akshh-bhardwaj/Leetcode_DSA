#include <stdlib.h>

/* Comparator for descending sort */
int compare(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

int minimumBoxes(int* apple, int appleSize, int* capacity, int capacitySize) {
    int totalApples = 0;
    
    // Sum all apples
    for (int i = 0; i < appleSize; i++) {
        totalApples += apple[i];
    }
    
    // Sort capacities in descending order
    qsort(capacity, capacitySize, sizeof(int), compare);
    
    int usedBoxes = 0;
    
    // Pick largest boxes first
    for (int i = 0; i < capacitySize; i++) {
        totalApples -= capacity[i];
        usedBoxes++;
        
        if (totalApples <= 0) {
            return usedBoxes;
        }
    }
    
    return usedBoxes; // guaranteed solution exists
}
