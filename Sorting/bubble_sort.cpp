#include <iostream>
#define SIZE 9

void bubbleSort(int*);
void printArr(int*);

int main(void)
{
    int Arr[SIZE] = { 13, 4, 81, 10, 12, 89, 68, 45, 37 };

    std::cout << "Before Sorting: " << std::endl;
    printArr(Arr);
    bubbleSort(Arr);
    std::cout << "After Sorting: " << std::endl;
    printArr(Arr);
}

void bubbleSort(int* Arr)
{
    for (int pass = 1; pass < SIZE; pass++) {
        for (int i = 0; i < SIZE - 1; i++) {
            if (Arr[i] > Arr[i + 1]) {
                std::swap(Arr[i], Arr[i + 1]);
            }
        }
    }
}

void printArr(int* Arr)
{
    for (int index = 0; index < SIZE; index++) {
        std::cout << Arr[index] << " ";
    }
    std::cout << std::endl;
}
