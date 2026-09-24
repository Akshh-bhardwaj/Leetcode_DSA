#include <stdio.h>
#include <stdlib.h>

// Structure representing each class in the heap
typedef struct {
    int pass;
    int total;
    double delta; // incremental gain if we add one extra student
} Class;

// Compute the incremental gain when adding one student
double gain(int pass, int total) {
    return (double)(pass + 1) / (total + 1) - (double)pass / total;
}

// Swap two class entries in the heap
void swap(Class* a, Class* b) {
    Class temp = *a;
    *a = *b;
    *b = temp;
}

// Push new entry into max-heap
void push(Class heap[], int* size, int pass, int total) {
    heap[*size].pass = pass;
    heap[*size].total = total;
    heap[*size].delta = gain(pass, total);
    int i = (*size)++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[parent].delta >= heap[i].delta) break;
        swap(&heap[parent], &heap[i]);
        i = parent;
    }
}

// Pop the top (max delta) entry
Class pop(Class heap[], int* size) {
    Class top = heap[0];
    heap[0] = heap[--(*size)];
    int i = 0;
    while (1) {
        int left = 2 * i + 1, right = left + 1, largest = i;
        if (left < *size && heap[left].delta > heap[largest].delta)
            largest = left;
        if (right < *size && heap[right].delta > heap[largest].delta)
            largest = right;
        if (largest == i) break;
        swap(&heap[i], &heap[largest]);
        i = largest;
    }
    return top;
}

double maxAverageRatio(int** classes, int classesSize, int* classesColSize, int extraStudents) {
    int n = classesSize;
    Class* heap = (Class*)malloc((n + extraStudents) * sizeof(Class));
    int heapSize = 0;

    // Build initial heap
    for (int i = 0; i < n; i++) {
        push(heap, &heapSize, classes[i][0], classes[i][1]);
    }

    // Distribute extra students
    for (int i = 0; i < extraStudents; i++) {
        Class top = pop(heap, &heapSize);
        top.pass++;
        top.total++;
        top.delta = gain(top.pass, top.total);
        push(heap, &heapSize, top.pass, top.total);
    }

    // Compute final average ratio
    double totalRatio = 0.0;
    while (heapSize > 0) {
        Class c = pop(heap, &heapSize);
        totalRatio += (double)c.pass / c.total;
    }

    free(heap);
    return totalRatio / n;
}
