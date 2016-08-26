#include <iostream>
#include <limits>
#include <vector>

enum {
    INFINITY = std::numeric_limits<int>::max()
};

void merge(std::vector<int>& myVector, int firstElement, int lastElementFirstPortion, int lastElement)
{
    int numOfElementsLeftPortion = lastElementFirstPortion - firstElement + 1;
    int numOfElementsRightPortion = lastElement - lastElementFirstPortion;

    // adding 1 for SENTINEL value
    std::vector<int> leftVector(numOfElementsLeftPortion + 1);
    std::vector<int> rightVector(numOfElementsRightPortion + 1);

    for (int i = 0; i < numOfElementsLeftPortion; i++) {
        leftVector[i] = myVector[firstElement + i];
    }

    for (int j = 0; j < numOfElementsRightPortion; j++) {
        rightVector[j] = myVector[lastElementFirstPortion + j + 1];
    }

    // SENTINEL value INFINITY added at the end of the vector
    leftVector[numOfElementsLeftPortion] = INFINITY;
    rightVector[numOfElementsRightPortion] = INFINITY;
    // index to track to sub portion
    int i = 0;
    int j = 0;

    for (int k = firstElement; k <= lastElement; k++) {
        if (leftVector[i] <= rightVector[j]) {
            myVector[k] = leftVector[i];
            i++;
        } else {
            myVector[k] = rightVector[j];
            j++;
        }
    }
}

void mergeSort(std::vector<int>& V, int start, int end)
{
    if (start < end) {
        int middle = (start + end) / 2;

        // divide and conquer and merging
        mergeSort(V, start, middle);
        mergeSort(V, middle + 1, end);

        merge(V, start, middle, end);
    }
}

void printFunc(std::vector<int>& V)
{
    for (const auto& elements : V) {
        std::cout << elements << " ";
    }
    std::cout << std::endl;
}

int main(void)
{
    std::vector<int> vec = { 44, 9, 11, 237, 5, 1, 7, 6, 13 };
    // calling mergeSort function
    mergeSort(vec, 0, vec.size() - 1);
    printFunc(vec);
}
