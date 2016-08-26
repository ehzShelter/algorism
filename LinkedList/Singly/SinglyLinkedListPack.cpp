#include <cassert>
#include <cstdio>
#include <new>

typedef struct sllist {
    char data;
    struct sllist* next;
} sllnode;

sllnode* head = nullptr;

void push(char character);
void pop(void);
void insertsorted(char x);
void RemoveDuplicates(void);
void InsertNth(char value, int position);
void append(char i);
bool Search(char value);
void deleteNth(int position);
void deleteData(char value);
int length(void);
void heapdelete(void);
void heapRecursivedelete(void);
void printlist(void);
void reversePrint(sllnode* headRef);
bool isEmpty(void);
void freeAllNodes(sllnode* node);

int main(void)
{
    InsertNth('M', 1);
    InsertNth('s', 3);
    InsertNth('L', 0);
    printlist();
    InsertNth('G', 1);
    InsertNth('y', 3);
    InsertNth('#', 2);
    printlist();
    InsertNth('^', 15);
    InsertNth('W', 5);
    InsertNth('B', 8);
    InsertNth('T', 9);
    printlist();

    InsertNth('M', 1);
    InsertNth('q', 2);
    InsertNth('s', 3);
    printlist();
    InsertNth('G', 1);
    InsertNth('y', 3);
    InsertNth('M', 2);
    printlist();
    InsertNth('*', 15);
    InsertNth('W', 5);
    InsertNth('B', 8);
    InsertNth('T', 10);
    printlist();

    InsertNth('I', 1);
    InsertNth('y', 3);
    InsertNth('A', 2);
    printlist();

    isEmpty();
    insertsorted('A');
    insertsorted('C');
    insertsorted('B');

    printlist();
    push('P');
    printlist();
    pop();
    printlist();

    insertsorted('Y');
    insertsorted('X');
    insertsorted('Y');

    printlist();
    RemoveDuplicates();
    printlist();

    InsertNth('R', 10);
    printlist();
    insertsorted('G');
    printlist();

    append('j');
    printlist();

    if (Search('G')) {
        printf("Found %c !", 'G');
        puts("Because.....");
        printlist();
    }

    deleteNth(2);
    printlist();
    deleteData('G');
    deleteData('Q');

    printlist();
    puts("NOW reversing the linked list");
    reversePrint(head);

    puts("NULL\n");
    printf("the LENGTH of SLL is now %d\n", length());

    heapdelete();

    isEmpty();

    puts("Again Insertion\n");
    insertsorted('F');
    insertsorted('U');
    insertsorted('C');
    insertsorted('K');
    printlist();
    heapRecursivedelete();
    return 0;
}

void push(char character)
{
    auto newNode = new (sllnode);

    newNode->data = character;
    newNode->next = nullptr;

    // quick check for empty list
    // for pushing element
    if (head != nullptr) {
        newNode->next = head;
    }

    head = newNode;
}

void pop(void)
{
    if (head == nullptr) {
        puts("nothing to pop out\n");
        return;
    }
    assert(head != nullptr);
    sllnode* PopOff = head;
    head = head->next;

    delete (PopOff);
}

void insertsorted(char x)
{
    auto newNode = new (sllnode);

    if (newNode == nullptr) {
        printf("there is no new sllnode\n");
        return;
    }

    newNode->data = x;
    newNode->next = nullptr;

    sllnode* inserter = nullptr;

    for (sllnode* scanner = head; scanner != nullptr; scanner = scanner->next) {
        if (scanner->data > x) {
            break;
        }

        else {
            inserter = scanner;
        }
    }

    if (inserter == nullptr) {
        newNode->next = head;
        head = newNode;
    }

    else {
        newNode->next = inserter->next;
        inserter->next = newNode;
    }
}

void RemoveDuplicates(void)
{
    sllnode* current = head;
    if (head == nullptr) {
        return;
    }

    while (current->next != nullptr) {
        if (current->data == current->next->data) {
            sllnode* nextNext = current->next->next;
            delete (current->next);
            current->next = nextNext;
        }
        else {
            current = current->next;
        }
    }
}

void InsertNth(char value, int position)
{
    if ((!isEmpty() || position == 1) && position > 0) {
        sllnode* inserter = nullptr;
        sllnode* scanner = head;

        for (int i = 1; i < position - 1; i++) {
            scanner = scanner->next;
            if (scanner == nullptr) {
                fprintf(stderr, "Invalid %dth(Nth) position Insertion\n,"
                                "so \"INSERTION SKIPPED\"\n",
                    position);
                return;
            }
        }

        auto newNode = new (sllnode);

        newNode->data = value;
        newNode->next = nullptr;

        if (position == 1 && isEmpty()) {
            head = newNode;
            return;
        }

        else if (position == 1 && !isEmpty()) {
            newNode->next = head;
            head = newNode;
            return;
        }

        inserter = scanner;

        newNode->next = inserter->next;
        inserter->next = newNode;
    }
    else {
        printf("\nLinked list is empty or invalid %dth position\n",position);
    }
}

void append(char i)
{
    auto newNode = new (sllnode);
    if (newNode == nullptr) {
        return;
    }

    newNode->data = i;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    }
    else {
        sllnode* crawler = head;
        while (crawler->next != nullptr) {
            crawler = crawler->next;
        }
        crawler->next = newNode;
    }
}

bool Search(char value)
{
    for (sllnode* crawler = head; crawler != nullptr; crawler = crawler->next) {
        if (crawler->data == value) {
            return true;
        }
    }
    printf("Your searching data %c is not found\n\n", value);
    return false;
}

void deleteNth(int position)
{
    sllnode* scanner = head;

    if (position == 1) {
        head = scanner->next;
        delete (scanner);
        return;
    }

    sllnode* deleter = nullptr;

    for (int i = 1; i < position - 1; i++) {
        if (scanner->next == nullptr) {
            puts("invalid delete operation,so \"skipped\"");
            return;
        }

        scanner = scanner->next;
    }

    deleter = scanner->next;
    scanner->next = deleter->next;
    delete (deleter);
}

void deleteData(char value)
{
    sllnode* scanner = head;

    sllnode* deleter = nullptr;
    while (scanner != nullptr) {
        if (scanner->data == value) {
            if (scanner == head) {
                head = scanner->next;
                delete (scanner);
            }

            else {
                deleter->next = scanner->next;
                delete (scanner);
            }
            break;
        }
        else {
            deleter = scanner;
            scanner = scanner->next;
        }
    }
    if (scanner == nullptr) {
        printf("Could n't find %c  :(:(\n", value);
    }
    else
        printf("Found %c!!!\n", value);
}

void printlist(void)
{
    printf("Your list now contains:\n ");
    for (sllnode* cursor = head; cursor != nullptr; cursor = cursor->next) {
        printf("%c--> ", cursor->data);
    }
    puts("NULL\n");
}

int length(void)
{
    int count = 0;
    for (sllnode* current = head; current != nullptr; current = current->next) {
        count++;
    }
    return count;
}

bool isEmpty(void)
{
    return (head == nullptr) ? 1 : 0;
}

void reversePrint(sllnode* headRef)
{
    if (headRef == nullptr) {
        return;
    }

    // print the list after head node
    reversePrint(headRef->next);

    printf(" %c--> ", headRef->data);
}

// loop based free SLL
void heapdelete(void)
{
    sllnode* HeapHacker = head;
    while (HeapHacker != nullptr) {
        sllnode* temp = HeapHacker;
        HeapHacker = HeapHacker->next;
        if (temp != nullptr) {
            delete (temp);
        }
    }
    head = nullptr;
}

void heapRecursivedelete(void)
{
    freeAllNodes(head);
    head = nullptr;
}

void freeAllNodes(sllnode* node)
{
    if (node == nullptr) {
        return;
    }

    if (node->next != nullptr) {
        freeAllNodes(node->next);
    }

    delete (node);
}
