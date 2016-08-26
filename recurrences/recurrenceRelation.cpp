#include <iostream>

int even(int k)
{
    if (k == 1) {
        return 0;
    } else {
        return even(k - 1) + 2;
    }
}

int kTHpowerOfTwo(int k)
{
    if (k == 0) {
        return 1;
    } else {
        return 2 * kTHpowerOfTwo(k - 1);
    }
}

int seqSearch(int* L, int i, int j, int x)
{
    if (i <= j) {
        if (L[i] == x) {
            return i;
        }

        else {
            return seqSearch(L, i + 1, j, x);
        }
    } else {
        return 0;
    }
}

int fact(int k)
{
    if (k == 0) {
        return 1;
    } else {
        return k * fact(k - 1);
    }
}

int evenSum(int num)
{
    if (num <= 0) {
        return 0;
    } else {
        // we are interested in odd numbers only
        if (num % 2 == 0) {
            return num + evenSum(num - 2);
        }
        // skip even numbers turn them into odd numbers
        else {
            return evenSum(num - 1);
        }
    }
}

int oddSum(int num)
{
    if (num <= 1) {
        return 1;
    } else {
        // we are interested in odd numbers only
        if (num % 2 == 1) {
            return num + oddSum(num - 2);
        }
        // skip even numbers turn them into odd numbers
        else {
            return oddSum(num - 1);
        }
    }
}

int evaluateNX(unsigned int n, int x)
{
    if (n == 1) {
        return x;
    } else {
        return x + evaluateNX(n - 1, x);
    }
}

int main(void)
{
    std::cout << even(5);
    std::cout << std::endl;
    std::cout << kTHpowerOfTwo(5);
    std::cout << std::endl;
    int arrayL[] = { 4, 5, 6, 7, 8, 9, 10 };

    std::cout << seqSearch(arrayL, 1, 5, 6);
    std::cout << std::endl;
    std::cout << fact(5);
    std::cout << std::endl;
    std::cout << evenSum(10);
    std::cout << std::endl;
    std::cout << oddSum(5);
    // std::cout << std::endl;
    // std::cout << oddSum(11);
    std::cout << std::endl;
    std::cout << evaluateNX(5, -5);
    std::cout << std::endl;
}
