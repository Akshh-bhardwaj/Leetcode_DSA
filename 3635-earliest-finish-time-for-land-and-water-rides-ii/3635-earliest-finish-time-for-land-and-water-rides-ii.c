int solve(int* start1, int start1Size, int* duration1, int duration1Size, int* start2, int start2Size, int* duration2, int duration2Size) {
    int finish1 = INT_MAX;
    for (int i = 0; i < start1Size; i++) {
        finish1 = fmin(finish1, start1[i] + duration1[i]);
    }

    int finish2 = INT_MAX;
    for (int j = 0; j < start2Size; j++) {
        finish2 = fmin(finish2, fmax(finish1, start2[j]) + duration2[j]);
    }

    return finish2;
}

int earliestFinishTime(int* landStartTime, int landStartTimeSize, int* landDuration, int landDurationSize, int* waterStartTime, int waterStartTimeSize, int* waterDuration, int waterDurationSize) {
    int landToWater = solve(landStartTime, landStartTimeSize,           landDuration, landDurationSize, waterStartTime, waterStartTimeSize, waterDuration, waterDurationSize);
    
    int waterToLand = solve(waterStartTime, waterStartTimeSize, waterDuration, waterDurationSize, landStartTime, landStartTimeSize, landDuration, landDurationSize);

    return fmin(landToWater, waterToLand);
}