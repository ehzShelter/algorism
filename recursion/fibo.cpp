#include <iostream>

using namespace std;

void printFibo(int size, int bp = 1, int p = 1)
{
    if (size <= 0) {
        return;
    }

    cout << bp << " " << p << " ";

    printFibo(size - 2, bp + p, p + (bp + p));
}

int main()
{
    printFibo(25);
}
