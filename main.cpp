#include <iostream>
#include <vector>
#include <cmath>

#ifdef TIMING
#include <ctime>
#endif

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

enum TEST_TYPE {
    SORTED,
    REVERSED,
    RANDOMIZED
};

std::vector<int> generateArray(unsigned long n, TEST_TYPE type) {
    std::vector<int> generatedArray(n);

    // Fill the array.
    switch (type) {
        case SORTED:
            for (int i = 0; i < n; i++) {
                generatedArray[i] = i;
            }
            break;
        case REVERSED:
            for (int i = 0; i < n; i++) {
                generatedArray[i] = (int) (n - 1);
            }
            break;
        case RANDOMIZED:
            for (int i = 0; i < n; i++) {
                generatedArray[i] = (int) (rand() % n);
            }
            break;
    }

    return generatedArray;
}

void runMethod(std::vector<int> &testVector) {
#ifdef TIMING
    clock_t start = clock();
#endif
    std::cout << "Test Output: " << BruteForceMedian(testVector) << std::endl;
#ifdef TIMING
    clock_t end = clock();
    std::cout << "Time: " << (end - start) << "ms With Number: " << testVector.size() << std::endl;
#endif
}

int main() {
    std::cout << "== Sorted Test ==" << std::endl;

    std::vector<int> testVector = generateArray(10, TEST_TYPE::SORTED);
    runMethod(testVector);

    testVector = generateArray(100, TEST_TYPE::SORTED);
    runMethod(testVector);

    testVector = generateArray(1000, TEST_TYPE::SORTED);
    runMethod(testVector);

    testVector = generateArray(10000, TEST_TYPE::SORTED);
    runMethod(testVector);

    std::cout << "== Reversed Test ==" << std::endl;

    testVector = generateArray(10, TEST_TYPE::REVERSED);
    runMethod(testVector);

    testVector = generateArray(100, TEST_TYPE::REVERSED);
    runMethod(testVector);

    testVector = generateArray(1000, TEST_TYPE::REVERSED);
    runMethod(testVector);

    testVector = generateArray(10000, TEST_TYPE::REVERSED);
    runMethod(testVector);

    std::cout << "== Random Test ==" << std::endl;

    testVector = generateArray(10, TEST_TYPE::RANDOMIZED);
    runMethod(testVector);

    testVector = generateArray(100, TEST_TYPE::RANDOMIZED);
    runMethod(testVector);

    testVector = generateArray(1000, TEST_TYPE::RANDOMIZED);
    runMethod(testVector);

    testVector = generateArray(10000, TEST_TYPE::RANDOMIZED);
    runMethod(testVector);

    return 0;
}