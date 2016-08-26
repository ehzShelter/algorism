#include <iostream>
#define SIZE 7

void insertionSort(int*);
void printArray(int*);

int main(void)
{
    int unsortedArr[SIZE] = { 3, 12, 55, 6, 9, 15, 2 };
    std::cout << "Before Sort: " << std::endl;
    printArray(unsortedArr);
    insertionSort(unsortedArr);
}

void insertionSort(int* arr)
{
    for (int rightIndex = 1; rightIndex < SIZE; rightIndex++) {
        int holdInplaceValue = arr[rightIndex];
        int backIndex = rightIndex - 1;
        while (backIndex >= 0 && arr[backIndex] > holdInplaceValue) {
            arr[backIndex + 1] = arr[backIndex];
            backIndex--;
        }
        arr[backIndex + 1] = holdInplaceValue;
    }

    std::cout << "After Sort: " << std::endl;
    printArray(arr);
}

void printArray(int* Array)
{
    for (int i = 0; i < SIZE; i++) {
        std::cout << Array[i] << " ";
    }
    std::cout << std::endl;
}
