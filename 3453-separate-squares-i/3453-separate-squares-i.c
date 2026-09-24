double areaBelowLine(int** squares, int squaresSize, double Y) {
    double area = 0.0;
    for (int i = 0; i < squaresSize; i++) {
        double sy = squares[i][1];
        double l  = squares[i][2];

        if (Y <= sy) {
            // no contribution
            continue;
        } else if (Y >= sy + l) {
            // full square below
            area += l * l;
        } else {
            // partially cut square
            area += (Y - sy) * l;
        }
    }
    return area;
}

double separateSquares(int** squares, int squaresSize, int* squaresColSize) {
    double totalArea = 0.0;
    double low = 1e18, high = -1e18;

    // calculate total area and bounds
    for (int i = 0; i < squaresSize; i++) {
        double y = squares[i][1];
        double l = squares[i][2];

        totalArea += l * l;
        if (y < low) low = y;
        if (y + l > high) high = y + l;
    }

    double target = totalArea / 2.0;

    // binary search for y-coordinate
    for (int i = 0; i < 80; i++) {
        double mid = (low + high) / 2.0;
        if (areaBelowLine(squares, squaresSize, mid) < target) {
            low = mid;
        } else {
            high = mid;
        }
    }

    return high;
}
