#include <iostream>

int sumDigits(int num)
{
    if (num / 10 == 0) {
        return num;
    }
    else {
        return ((num % 10) + sumDigits(num / 10));
    }
}

int main(void)
{
    int input = 0;
    std::cin >> input;

    std::cout << sumDigits(input) << std::endl;
}
