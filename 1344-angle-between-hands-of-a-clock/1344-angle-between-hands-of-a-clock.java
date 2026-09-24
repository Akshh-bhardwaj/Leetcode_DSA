class Solution {
    public double angleClock(int h, int m) {
        return Math.acos(Math.cos((330 * h + 5.5 * m) * 0.0174532925)) * 57.2957795;
    }
}