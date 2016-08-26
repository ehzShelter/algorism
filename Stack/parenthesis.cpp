#include <iostream>
#include <string>
#define MAX_SIZE 5

class Stack {
private:
    char A[MAX_SIZE];
    int top;

public:
    // constructor with member initializer list
    Stack();
    void Print();
    void push(char x);
    void pop();
    int topReturn();
    int areParenthesisBalanced(std::string exp);
    bool arePair(char opening, char closing);
    bool isFull();
    bool isEmpty();

    static void errorMsg();
};

Stack::Stack()
    : top(-1)
{
}

void Stack::push(char x)
{
    if (isFull()) {
        std::cout << "Error: stack overflow\n";
        return;
    }
    A[++top] = x;
}

void Stack::pop()
{
    if (top == -1) {
        std::cout << "Error : Underflow\n";
        std::cout << "Error: No element to pop\n";
        return;
    }
    top--;
}

int Stack::topReturn()
{
    return A[top];
}

bool Stack::isEmpty()
{
    if (top == -1) {
        return true;
    }
    else {
        return false;
    }
}

bool Stack::isFull()
{
    if (top >= MAX_SIZE - 1) {
        return true;
    }
    else {
        return false;
    }
}

bool Stack::arePair(char opening, char closing)
{
    if (opening == '(' && closing == ')') {
        return true;
    }
    else if (opening == '{' && closing == '}') {
        return true;
    }
    else if (opening == '[' && closing == ']') {
        return true;
    }
    return false;
}

void Stack::Print()
{
    std::cout << "Stack : " << std::endl;
    for (int i = 0; i <= top; i++){
        std::cout << A[i];
    }
    std::cout << std::endl;
}

void Stack::errorMsg()
{
    std::cout << "Stack Overflow or Something Went Wrong" << std::endl;
}

int Stack::areParenthesisBalanced(std::string exp)
{
    for (size_t i = 0; i < exp.size(); i++) {
        if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[') {
            if (isFull()) {
                return -1;
            }
            else {
                push(exp[i]);
            }
        }

        else if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']') {
            if (isEmpty() || !arePair(topReturn(), exp[i])) {
                return 0;
            }

            else {
                pop();
            }
        }
    }
    return isEmpty() ? 1 : 0;
}

int main(void)
{
    std::string expression;
    std::cout << "Enter an expression:  ";
    getline(std::cin, expression);

    if (expression.empty()) {
        std::cout << "Empty String..Nothing to compare\n";
        return -1;
    }

    Stack myStack;

    int x = myStack.areParenthesisBalanced(expression);
    if (x == 1) {
        std::cout << "Balanced\n";
    }
    else if (x == 0) {
        std::cout << "Not Balanced\n";
    }
    else {
        Stack::errorMsg();
    }
}
