#include <cassert>
#include <cstdio>

struct node {
    int value;
    struct node* next;
};

struct queue {
    struct node* head;
    struct node* tail;
};

typedef struct queue* q;

struct queue* queueCreate(void)
{
    struct queue* q = new (struct queue);

    q->head = q->tail = NULL;

    return q;
}

// push a new value onto top of Queue
void enq(struct queue* q, int value)
{
    struct node* e = new (struct node);
    assert(e);

    e->value = value;

    // Because I will be the tail, nobody is behind me
    e->next = NULL;

    if (q->head == NULL) {
        // If the queue was empty, I become the head
        q->head = e;
    } else {
        // Otherwise I get in line after the old tail
        q->tail->next = e;
    }

    // I become the new tail
    q->tail = e;
}

int queueEmpty(const struct queue* q)
{
    return (q->head == NULL);
}

int deq(struct queue* q)
{
    assert(!queueEmpty(q));

    int ret = q->head->value;

    // patch out first element
    struct node* e = q->head;
    q->head = e->next;

    delete (e);

    return ret;
}

// print contents of queue on a single line, head first
void queuePrint(struct queue* q)
{
    for (struct node* e = q->head; e != NULL; e = e->next) {
        printf("%d ", e->value);
    }
    putchar('\n');
}

// free a queue and all of its elements
void queueDestroy(struct queue* q)
{
    while (!queueEmpty(q)) {
        deq(q);
    }

    delete (q);
}

void operation(void)
{
    struct queue* q = queueCreate();

    for (int i = 0; i < 5; i++) {
        printf("enq %d\n", i);
        enq(q, i);
        queuePrint(q);
    }

    while (!queueEmpty(q)) {
        printf("deq gets %d\n", deq(q));
        queuePrint(q);
    }

    queueDestroy(q);
}

int main(void)
{
    operation();
}
