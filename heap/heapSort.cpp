#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

// Algorithm is taken from "Introduction to Algorithm (CLRS)"
// prototypes signatures
void maxHeapify(std::vector<int>&, int, int);
int left(int);
int right(int);
void buildMaxHeap(std::vector<int>&);
void heapSort(std::vector<int>&);
void printArray(std::vector<int>&, std::string);

int main(int argc, char* argv[])
{
    // excluding the executable name from command-line argument
    argc--;
    argv++;
    std::vector<int> A(argc);

    for (size_t i = 0; i < A.size(); i++) {
        A[i] = std::atoi(argv[i]);
    }

    if (argc < 2) {
        std::cout << "More arguments required" << std::endl;
        return -1;
    }

    printArray(A, "Before Sorting >>>> ");

    heapSort(A);

    printArray(A, "After Sorting >>>>> ");
}

void printArray(std::vector<int>& arr, std::string argStr = "")
{
    std::cout << argStr;
    for (auto element : arr) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

void maxHeapify(std::vector<int>& A, int root, int heapSize)
{
    int largest = 0;
    int leftChild = left(root);
    int rightChild = right(root);

    if (leftChild <= heapSize && A[leftChild] > A[root]) {
        largest = leftChild;
    } else {
        largest = root;
    }

    if (rightChild <= heapSize && A[rightChild] > A[largest]) {
        largest = rightChild;
    }

    if (largest != root) {
        std::swap(A[root], A[largest]);
        maxHeapify(A, largest, heapSize);
    }
}

void buildMaxHeap(std::vector<int>& A)
{
    int heapSize = A.size() - 1;
    for (int i = A.size() / 2; i >= 0; i--) {
        maxHeapify(A, i, heapSize);
    }
}

void heapSort(std::vector<int>& A)
{
    int heapSize = A.size() - 1;
    buildMaxHeap(A);
    for (int i = A.size() - 1; i > 0; i--) {
        std::swap(A[0], A[i]);
        heapSize--;
        maxHeapify(A, 0, heapSize);
    }
}

int left(int root)
{
    return 2 * root + 1;
}

int right(int root)
{
    return 2 * root + 2;
}
