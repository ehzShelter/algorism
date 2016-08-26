#include <iostream>
#define LENGTH 7

int indexOfMinimum(int*, int);
void printArr(int*);
void selectionSort(int*);
void swapFunc(int*, int, int);

int main(void)
{
    int array[7] = { 22, 11, 99, 88, 9, 7, 42 };
    std::cout << "Before Sort: " << std::endl;
    printArr(array);
    selectionSort(array);
    std::cout << "After Sort: " << std::endl;
    printArr(array);
}

void swapFunc(int* array, int firstIndex, int secondIndex)
{
    int temp = array[firstIndex];
    array[firstIndex] = array[secondIndex];
    array[secondIndex] = temp;
}

int indexOfMinimum(int* array, int startIndex)
{
    int minValue = array[startIndex];
    int minIndex = startIndex;

    for (int i = minIndex + 1; i < LENGTH; i++) {
        if (array[i] < minValue) {
            minIndex = i;
            minValue = array[i];
        }
    }
    return minIndex;
}

void selectionSort(int* array)
{
    for (int walk = 0; walk < LENGTH; walk++) {
        int select = indexOfMinimum(array, walk);
        swapFunc(array, select, walk);
    }
}

void printArr(int* array)
{
    for (int i = 0; i < LENGTH; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}
