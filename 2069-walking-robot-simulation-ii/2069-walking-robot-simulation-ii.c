#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int w;
    int h;
    int p;    
    int curr; 
    bool moved; 
} Robot;

Robot* robotCreate(int width, int height) {
    Robot* obj = (Robot*)malloc(sizeof(Robot));
    obj -> w = width;
    obj -> h = height;
    obj -> p = (width + height - 2) << 1; 
    obj -> curr = 0;
    obj -> moved = false;
    return obj;
}

void robotStep(Robot* obj, int num) {
    obj -> moved = true;
    obj -> curr = (obj -> curr + num) % obj -> p;
}

int* robotGetPos(Robot* obj, int* retSize) {
    *retSize = 2;
    int* pos = (int*)malloc(2 * sizeof(int));
    
    int w = obj -> w;
    int h = obj -> h;
    int curr = obj -> curr;
    int p = obj -> p;

    if (curr < w) {
        pos[0] = curr;
        pos[1] = 0;
    } else if (curr < w + h - 1) {
        pos[0] = w - 1;
        pos[1] = curr - w + 1;
    } else if (curr < (w << 1) + h - 2) {
        pos[0] = (w << 1) + h - 3 - curr;
        pos[1] = h - 1;
    } else {
        pos[0] = 0;
        pos[1] = p - curr;
    }
    
    return pos;
}

char* robotGetDir(Robot* obj) {
    if (!obj -> moved) {
        return "East";
    }
    
    if (obj -> curr == 0) {
        return "South";
    }
    
    int w = obj -> w;
    int h = obj -> h;
    int curr = obj -> curr;
    
    if (curr < w) {
        return "East";
    } else if (curr < w + h - 1) {
        return "North";
    } else if (curr < (w << 1) + h - 2) {
        return "West";
    }
    
    return "South";
}

void robotFree(Robot* obj) {
    free(obj);
}

/**
 * Your Robot struct will be instantiated and called as such:
 * Robot* obj = robotCreate(width, height);
 * robotStep(obj, num);
 
 * int* param_2 = robotGetPos(obj, retSize);
 
 * char* param_3 = robotGetDir(obj);
 
 * robotFree(obj);
*/