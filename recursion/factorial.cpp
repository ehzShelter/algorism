#include <iostream>

int findFact(int num)
{
    if (num == 1) {
        return num;
    }
    else {
        return (num + findFact(num - 1));
    }
}

int main()
{
    int input = 0;
    std::cin >> input;

    std::cout << findFact(input) << std::endl;
}
