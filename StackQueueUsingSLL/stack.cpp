#include <cassert>
#include <cstdio>

struct node {
    int value;
    struct node* next;
};

typedef struct node* Stack;

#define STACK_EMPTY (0)

void stackPush(Stack* s, int value)
{
    struct node* e = new (struct node);
    assert(e);

    e->value = value;
    e->next = *s;
    *s = e;
}

int stackEmpty(const Stack* s)
{
    return (*s == 0);
}

int stackPop(Stack* s)
{
    assert(!stackEmpty(s));

    int ret = (*s)->value;

    struct node* e = *s;
    *s = e->next;
    delete (e);

    return ret;
}

void stackPrint(const Stack* s)
{
    for (struct node* e = *s; e != 0; e = e->next) {
        printf("%d ", e->value);
    }

    putchar('\n');
}

void operation(void)
{
    Stack s = STACK_EMPTY;

    for (int i = 0; i < 5; i++) {
        printf("push %d\n", i);
        stackPush(&s, i);
        stackPrint(&s);
    }

    while (!stackEmpty(&s)) {
        printf("pop gets %d\n", stackPop(&s));
        stackPrint(&s);
    }
}

int main(void)
{
    operation();
}
