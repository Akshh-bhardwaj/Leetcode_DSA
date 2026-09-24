#include <stdio.h>

double findMedianSortedArrays(int* nums1, int m, int* nums2, int n) {
    if (m > n) {
        // Always binary search on smaller array
        return findMedianSortedArrays(nums2, n, nums1, m);
    }

    int low = 0, high = m;
    while (low <= high) {
        int partitionX = (low + high) / 2;
        int partitionY = (m + n + 1) / 2 - partitionX;

        int maxLeftX = (partitionX == 0) ? -1000000 : nums1[partitionX - 1];
        int minRightX = (partitionX == m) ? 1000000 : nums1[partitionX];

        int maxLeftY = (partitionY == 0) ? -1000000 : nums2[partitionY - 1];
        int minRightY = (partitionY == n) ? 1000000 : nums2[partitionY];

        if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
            // Found correct partition
            if ((m + n) % 2 == 0) {
                return (double)( ( (maxLeftX > maxLeftY) ? maxLeftX : maxLeftY ) + 
                                 ( (minRightX < minRightY) ? minRightX : minRightY ) ) / 2.0;
            } else {
                return (double)( (maxLeftX > maxLeftY) ? maxLeftX : maxLeftY );
            }
        } else if (maxLeftX > minRightY) {
            high = partitionX - 1;
        } else {
            low = partitionX + 1;
        }
    }

    return -1.0;  // Should not reach here if input is valid
}
