#include <iostream>
#include <stack>
#include <string>

bool IsOperand(char ch)
{
    if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
        return true;
    }
    return false;
}

bool IsOperator(char C)
{
    if (C == '+' || C == '-' || C == '*' || C == '/' || C == '^') {
        return true;
    }
    return false;
}

bool isViable(char ch)
{
    if (!IsOperand(ch) || !IsOperator(ch) || ch == '(' || ch == ')') {
        return false;
    }
    return true;
}

bool IsRightAssociative(char op)
{
    if (op == '^') {
        return true;
    }
    return false;
}

int GetOperatorWeight(char op)
{
    int weight = -1;
    switch (op) {
    case '+':
    case '-':
        weight = 1;
        break;
    case '*':
    case '/':
        weight = 2;
        break;
    case '^':
        weight = 3;
        break;
    }
    return weight;
}

bool HasHigherPrecedence(char op1, char op2)
{
    int op1Weight = GetOperatorWeight(op1);
    int op2Weight = GetOperatorWeight(op2);

    // If operators have equal precedence, return true if they are left associative.
    // BUT REMEMBER...return false, if right associative.
    // if operator is left-associative, left one should be given priority.
    if (op1Weight == op2Weight) {
        if (IsRightAssociative(op1)) {
            return false;
        }
        else {
            return true;
        }
    }
    return (op1Weight > op2Weight) ? true : false;
}

std::string InfixToPostfix(std::string expression)
{
    std::stack<char> S;
    std::string postfix = "";
    for (auto& elem : expression) {
        if (isViable(elem)) {
            continue;
        }
        // If character is operator, pop two elements from stack, perform operation and push the result back.
        else if (IsOperator(elem)) {
            while (!S.empty() && S.top() != '(' && HasHigherPrecedence(S.top(), elem)) {
                postfix += S.top();
                S.pop();
            }
            S.push(elem);
        }
        else if (IsOperand(elem)) {
            postfix += elem;
        }
        else if (elem == '(') {
            S.push(elem);
        }
        else if (elem == ')') {
            while (!S.empty() && S.top() != '(') {
                postfix += S.top();
                S.pop();
            }
            S.pop();
        }
    }

    while (!S.empty()) {
        postfix += S.top();
        S.pop();
    }

    return postfix;
}

void show(std::string infix, std::string postfix)
{
    std::cout << "Infix = " << infix << " : ";
    std::cout << "postfix = " << postfix << std::endl;
}

int main(void)
{
    std::string expression = "A+(B*C-(D/E^F)*G)*H";
    std::string postfixExp = InfixToPostfix(expression);
    show(expression, postfixExp);

    std::string mathExpression = "5*4/(5^2)+(6^2^3)";
    std::string postfixMath = InfixToPostfix(mathExpression);
    show(mathExpression, postfixMath);
}
