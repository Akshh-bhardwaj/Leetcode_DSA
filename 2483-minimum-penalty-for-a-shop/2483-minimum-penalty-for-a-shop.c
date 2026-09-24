int bestClosingTime(char* customers) {
    int penalty = 0;
    int i = 0;

    // Count total 'Y' initially (closing at hour 0)
    while (customers[i] != '\0') {
        if (customers[i] == 'Y')
            penalty++;
        i++;
    }

    int minPenalty = penalty;
    int bestHour = 0;

    // Try closing at hour 1 to n
    for (int j = 1; customers[j - 1] != '\0'; j++) {
        if (customers[j - 1] == 'Y')
            penalty--;   // served a customer
        else
            penalty++;   // open but no customer

        if (penalty < minPenalty) {
            minPenalty = penalty;
            bestHour = j;
        }
    }

    return bestHour;
}
