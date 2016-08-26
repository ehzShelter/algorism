#include <iostream>
#include <vector>

int partition(std::vector<int>& numbers, int first, int last)
{
    int pivot = numbers[last];
    int wallIndex = first - 1;
    for (int iterator = first; iterator < last; iterator++) {
        if (numbers[iterator] <= pivot) {
            wallIndex++;
            std::swap(numbers[wallIndex], numbers[iterator]);
        }
    }
    std::swap(numbers[wallIndex + 1], numbers[last]);
    return (wallIndex + 1);
}

void tailRecursiveQuickSort(std::vector<int>& numbers, int first, int last)
{
    while (first < last) {
        // wall determine the current location
        int wall = partition(numbers, first, last);
        tailRecursiveQuickSort(numbers, first, wall - 1);
        first = wall + 1;
    }
}

void print(std::vector<int>& V)
{
    for (const auto& element : V) {
        std::cout << element << " ";
    }
}

int main(void)
{
    std::vector<int> numbers = { 44, 9, 237, 11, 34, 5, 345, 1, 3 };
    tailRecursiveQuickSort(numbers, 0, numbers.size() - 1);
    print(numbers);
}
