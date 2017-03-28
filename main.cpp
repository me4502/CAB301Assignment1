#include <iostream>
#include <vector>
#include <cmath>

/**
 * Returns the median value in a given vector A of n numbers. This is
 * the kth element, where k = ceil(n/2), if the vector was sorted.
 *
 * @param input The input vector to find the median of
 * @return The median value in the vector
 */
int BruteForceMedian(std::vector<int> &input) {
    // Calculate the half-way index of the array.
    int k = (int) std::ceil(input.size() / 2.0);

    for (int i = 0; i < input.size(); i++) {
        int numSmaller = 0;
        int numEqual = 0;

        for (int j = 0; j < input.size(); j++) {
            // Calculate number of array items that are smaller, and equal.
            if (input[j] < input[i]) {
                numSmaller ++;
            } else if (input[j] == input[i]) {
                numEqual ++;
            }
        }

        if (numSmaller < k && k <= (numSmaller + numEqual)) {
            return input[i];
        }
    }

    return 0;
}

int main() {
    std::vector<int> testVector = {0, 1, 2, 3, 4, 5};
    std::cout << "Test Output: " << BruteForceMedian(testVector) << std::endl;

    testVector = {1, 5, 3, 9, 4};
    std::cout << "Test Output: " << BruteForceMedian(testVector) << std::endl;

    testVector = {5, 4, 3, 2, 1};
    std::cout << "Test Output: " << BruteForceMedian(testVector) << std::endl;
    return 0;
}