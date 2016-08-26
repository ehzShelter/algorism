#include <cstdio>
#include <cstdbool>

#define MAXSIZE 101

int A[MAXSIZE];
int top = -1; // empty stack

void push(int x);
void pop(void);
void printStack(void);
bool isEmpty(void);
bool isFull(void);

int main(void)
{
    push(2);
    printStack();
    push(4);
    printStack();
    push(5);
    printStack();
    pop();
    printStack();
    push(12);
    printStack();
}

bool isEmpty(void)
{
    if (top == -1) {
        return true;
    }
    else {
        return false;
    }
}

bool isFull(void)
{
    // overflow sanity check
    if (top == MAXSIZE - 1) {
        printf("Error: Stack Overflow\n");
        return true;
    }
    else {
        return false;
    }
}

void push(int x)
{
    if (!isFull()) {
        A[++top] = x;
    }
}

void pop(void)
{
    top--;
    if (isEmpty()) {
        printf("There is no element to pop out\n");
        return;
    }
}

void printStack(void)
{
    printf("STACK : ");
    for (int i = 0; i <= top; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

