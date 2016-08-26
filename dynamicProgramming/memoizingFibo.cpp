#include <iostream>
#include <map>

int mfib(int num)
{
    static std::map<int, int> memo{ { 0, 0 }, { 1, 1 } };

    auto found = memo.find(num);
    if (found != std::end(memo)) {
        return found->second;
    }

    int result = mfib(num - 1) + mfib(num - 2);
    memo[num] = result;
    return result;
}

int main(void)
{
    std::cout << mfib(8) << std::endl;
    std::cout << mfib(10000) << std::endl;
}
