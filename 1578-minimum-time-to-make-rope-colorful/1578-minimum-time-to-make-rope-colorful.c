int minCost(char * colors, int* neededTime, int neededTimeSize){
    int totalTime = 0;

    // Loop through balloons
    for (int i = 1; i < neededTimeSize; i++) {
        // If two adjacent balloons have same color
        if (colors[i] == colors[i - 1]) {
            // Remove the one with smaller time
            if (neededTime[i] < neededTime[i - 1]) {
                totalTime += neededTime[i];
                neededTime[i] = neededTime[i - 1]; // keep larger one for next compare
            } else {
                totalTime += neededTime[i - 1];
            }
        }
    }

    return totalTime;
}
