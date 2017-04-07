#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>

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
        int numSmaller = 0; // Number of elements smaller than input[i];
        int numEqual = 0; // Number of elements equal to input[i];

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
    SORTED = 0,
    REVERSED = 1,
    RANDOMIZED = 2
};

std::vector<int> generateArray(unsigned long n, TEST_TYPE type) {
    if (n <= 0) {
        n = 1;
    }
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
                generatedArray[i] = (int) (n - i - 1);
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
    int output = BruteForceMedian(testVector);
#ifdef TIMING
    double duration = (std::clock() - start) / (CLOCKS_PER_SEC / 1000.0);
    std::cout << "Time: " << duration << "ms With Number: " << testVector.size() << std::endl;
#elif TEST
    std::vector<int> sortedVector(testVector);
    std::sort(sortedVector.begin(), sortedVector.end());

    // The following median-algorithm is sourced from http://stackoverflow.com/a/2114817/3105532 on 7/4/2017
    // An existing implementation was chosen as it has been marked as correct, as well as voted on by a community
    int testOutput;
    if (sortedVector.size() % 2 == 0) {
        testOutput = (sortedVector[sortedVector.size() / 2 - 1] + sortedVector[sortedVector.size() / 2]) / 2;
    } else {
        testOutput = sortedVector[sortedVector.size() / 2];
    }

    std::cout << "Result: " << output << ", Actual median: " << testOutput;
    if (output == testOutput) {
        std::cout << ". PASS" << std::endl;
    } else {
        std::cout << ". FAILURE: ";

        if (std::find(sortedVector.begin(), sortedVector.end(), testOutput) == sortedVector.end()) {
            std::cout << "(AVERAGED) ";
        }

        std::ostringstream testVectorString;
        testVectorString << "[";
        std::copy(testVector.begin(), testVector.end()-1, std::ostream_iterator<int>(testVectorString, ","));
        testVectorString << testVector.back() << "]";

        std::cout << testVectorString.str() << std::endl;
    }
#elif LOGGING

#else
    std::cout << "Test Output: " << output << std::endl;
#endif
}

std::vector<unsigned long> testCases = {10, 100, 1000, 10000};

#ifdef TEST
#define TEST_COUNT 1
#else
#define TEST_COUNT 10
#endif

int main() {
    std::vector<int> testVector;

    for (int n = 0; n < TEST_COUNT; n++) {
        std::cout << "== Sorted Test ==" << std::endl;

        for (int i = 0; i < testCases.size(); i++) {
            testVector = generateArray(testCases[i], TEST_TYPE::SORTED);
            runMethod(testVector);
        }

        std::cout << "== Reversed Test ==" << std::endl;

        for (int i = 0; i < testCases.size(); i++) {
            testVector = generateArray(testCases[i], TEST_TYPE::REVERSED);
            runMethod(testVector);
        }

        std::cout << "== Random Test ==" << std::endl;

        for (int i = 0; i < testCases.size(); i++) {
            testVector = generateArray(testCases[i], TEST_TYPE::RANDOMIZED);
            runMethod(testVector);
        }
    }

#ifdef TEST
    std::cout << "== Random Length Random Test ==" << std::endl;
    for (int i = 0; i < 50; i++) {
        testVector = generateArray((unsigned long) (rand() % 100), TEST_TYPE::RANDOMIZED);
        runMethod(testVector);
    }
#endif

    return 0;
}