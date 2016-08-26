#include <iostream>
#include <string>
#include <stack>
#define TO_DIGIT(ch) (ch - '0')

int carry;
std::stack<int> finalStack;

void pushing(std::string myNumber, std::stack<int>& stackRef);
int topPop(std::stack<int>& myStack);
void finalResult(int tempTwoSum);
void showFinalStack(void);
void poppingSum(std::stack<int>& firstStack, std::stack<int>& secondStack);
std::string input(std::string str);

int main(void)
{
    std::stack<int> firstStack;
    std::stack<int> secondStack;

    std::string numExpressionOne, numExpressionTwo;

    numExpressionOne = input("first");
    numExpressionTwo = input("second");
    pushing(numExpressionOne, firstStack);
    pushing(numExpressionTwo, secondStack);
    poppingSum(firstStack, secondStack);
    showFinalStack();
}

void pushing(std::string myNumber, std::stack<int>& stackRef)
{
    for (auto number : myNumber) {
        stackRef.push((number));
    }
}

int topPop(std::stack<int>& myStack)
{
    if (!myStack.empty()) {
        int number = TO_DIGIT(myStack.top());
        myStack.pop();
        return number;
    }
    return 0;
}

void finalResult(int tempTwoSum)
{
    int sum = tempTwoSum % 10;
    carry = tempTwoSum / 10;
    finalStack.push(sum);
}

void showFinalStack(void)
{
    while (!finalStack.empty()) {
        std::cout << finalStack.top();
        finalStack.pop();
    }
    std::cout << std::endl;
}

void poppingSum(std::stack<int>& firstStack, std::stack<int>& secondStack)
{
    while (!firstStack.empty() || !secondStack.empty()) {
        int addTwo = topPop(firstStack) + topPop(secondStack) + carry;
        finalResult(addTwo);
    }

    if (carry) {
        finalStack.push(carry);
    }
}

std::string input(std::string str)
{
    std::string expression;
    std::cout << "Please enter your " << str << " number : " << std::endl;
    std::cin >> expression;
    return expression;
}

