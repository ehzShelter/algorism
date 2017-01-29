#include <algorithm>
#include <vector>
#include <chrono>
#include <iostream>

int iterativeBinarySearch(std::vector<int> A, int v, size_t low, size_t high)
{
    while (low <= high) {
        size_t mid = (low + high) / 2;
        if (v == A[mid]) {
            return mid;
        } else if (v > A[mid]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int recursiveBinarySearch(std::vector<int> A, int v, size_t low, size_t high)
{
    if (low > high) {
        return -1;
    }

    size_t mid = (low + high) / 2;
    if (v == A[mid]) {
        return mid;
    } else if (v > A[mid]) {
        return recursiveBinarySearch(A, v, mid + 1, high);
    } else {
        return recursiveBinarySearch(A, v, low, mid - 1);
    }
}

int main(void)
{
    std::vector<int> unSorted = {};

    size_t yourPreferredSize = 0;

    std::cout << "Enter your prefer size: ";
    std::cin >> yourPreferredSize;

    for (size_t i = 0; i < yourPreferredSize; i++) {
        int val = {};
        std::cin >> val;
        unSorted.push_back(val);
    }

    std::sort(unSorted.begin(), unSorted.end(), [](int a, int b) {
        return b > a;
    });

    std::vector<int> sorted = unSorted;

    int searchObject = {};
    std::cout << "Which value you wanted to search: ";
    std::cin >> searchObject;

    int low = 0;
    int high = sorted.size() - 1;

    std::cout << "iterativeBinarySearch:" << std::endl;
    std::clock_t iterativeBS_start = std::clock();
    if (iterativeBinarySearch(sorted, searchObject , low, high)  == -1) {
        std::cout << searchObject << " Not Found !!\n";
    }
    else {
        std::cout << searchObject << " Found !!\n";
    }
    std::clock_t iterativeBS_end = std::clock();


    std::cout << "CPU time used: "
              << 1000.0 * (iterativeBS_end - iterativeBS_start) / CLOCKS_PER_SEC << " miliseconds\n";


    std::cout << "recursiveBinarySearch:" << std::endl;
    std::clock_t recursiveBS_start = std::clock();
    if (recursiveBinarySearch(sorted, searchObject, low, high)  == -1) {
        std::cout << searchObject << " Not Found !!\n";
    }
    else {
        std::cout << searchObject << " Found !!\n";
    }
    std::clock_t recursiveBS_end = std::clock();
    std::cout << "CPU time used: "
              << 1000.0 * (recursiveBS_end - recursiveBS_start) / CLOCKS_PER_SEC << " miliseconds\n";
}
