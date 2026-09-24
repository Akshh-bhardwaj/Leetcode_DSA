int countOdds(int low, int high) {
    // Number of odd integers in [low, high]
    int oddsUpToHigh = (high + 1) / 2;
    int oddsBeforeLow = low / 2;      // odds up to (low - 1)
    return oddsUpToHigh - oddsBeforeLow;
}
