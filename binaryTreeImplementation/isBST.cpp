#include <cassert>
#include <climits>
#include <iostream>
#include <regex>

typedef struct binarynodeTree {
    int data;
    struct binarynodeTree* leftChild;
    struct binarynodeTree* rightChild;
} node;

node* root = nullptr;

void appRun(void);
node* GetNewnode(int data);
node* dataInsert(node* root, int data);
void BSTprettyprint(node* root, int pos);
bool validate(const std::string& data, const std::string& expression);
std::string inputData(const std::string& fieldName,
    const std::string& expression);
void deleteWholeTree(node* root);
bool isBstUtil(node* root, int minValue, int maxValue);
bool IsBinarySearchTree(node* root);
node* badDataInsert(node* root, int data);

int main(void)
{
    appRun();
    // delete whole tree for releasing allocated heap memory
    deleteWholeTree(root);
}

node* GetNewnode(int data)
{
    node* newnode = new (node);
    // Performs compile-time assertion checking
    assert(newnode);
    newnode->data = data;
    newnode->leftChild = newnode->rightChild = nullptr;
    return newnode;
}

node* dataInsert(node* root, int data)
{
    if (root == nullptr) {
        root = GetNewnode(data);
    }
    // if data to be inserted is lesser(equal), insert in leftChild subtree.
    else if (data <= root->data) {
        root->leftChild = dataInsert(root->leftChild, data);
    }
    // else, insert in rightChild subtree.
    else {
        root->rightChild = dataInsert(root->rightChild, data);
    }
    return root;
}

node* badDataInsert(node* root, int data)
{
    if (root == nullptr) {
        root = GetNewnode(data);
    }
    // if data to be inserted is lesser(equal), insert in leftChild subtree.
    else if (data >= root->data) {
        root->leftChild = dataInsert(root->leftChild, data);
    }
    // else, insert in rightChild subtree.
    else {
        root->rightChild = dataInsert(root->rightChild, data);
    }
    return root;
}

void deleteWholeTree(node* root)
{
    node* current = root;
    if (current == nullptr) {
        return;
    }

    deleteWholeTree(current->leftChild);
    deleteWholeTree(current->rightChild);

    delete current;
    current = nullptr; // neccessary to make that current pointer null
}

// BSTprettyprint FROM Stack Overflow for easy visuals
// http://stackoverflow.com/questions/3899636/how-can-i-print-a-binary-tree-search-class-vertically

void BSTprettyprint(node* root, int pos = 0)
{
    if (root == nullptr) {
        for (int i = 0; i < pos; ++i) {
            std::cout << "\t";
        }
        std::cout << 'X' << std::endl;
        return;
    }

    BSTprettyprint(root->rightChild, pos + 1);

    for (int i = 0; i < pos; i++) {
        std::cout << "\t";
    }
    std::cout << root->data << std::endl;
    BSTprettyprint(root->leftChild, pos + 1);
}

bool validate(const std::string& data, const std::string& expression)
{
    // regex c++11
    // http://cpprocks.com/files/c++11-regex-cheatsheet.pdf
    std::regex validationExpression = std::regex(expression);
    return std::regex_match(data, validationExpression);
}

std::string inputData(const std::string& fieldName,
    const std::string& expression)
{
    std::string data;

    std::cout << "Enter " << fieldName << ": ";
    getline(std::cin, data);

    // validate the data
    while (!(validate(data, expression))) {
        std::cout << "Invalid " << fieldName << ".\n";
        std::cout << "Enter " << fieldName << ": ";

        getline(std::cin, data);
    }
    return data;
}

bool isBstUtil(node* root, int minValue, int maxValue)
{
    if (root == nullptr) {
        return true;
    }
    if (root->data > minValue && root->data <= maxValue && isBstUtil(root->leftChild, minValue, root->data) && isBstUtil(root->rightChild, root->data, maxValue)) {
        return true;
    } else {
        return false;
    }
}

bool IsBinarySearchTree(node* root)
{
    return isBstUtil(root, INT_MIN, INT_MAX);
}

void appRun(void)
{
    int choice;
    do {
        std::cout << "\nMENU\n\n"
                  << "1 - insertData\n"
                  << "2 - prettyPrint\n"
                  << "3 - IsBinarySearchTree\n"
                  << "4 - badDataInsert\n"
                  << "0 - quit\n\n";

        choice = std::stoi(inputData("choice", "\\d+"));

        if (choice == 0) {
            std::cout << "Programm quits\n";
        } else if (choice == 1) {
            int val = std::stoi(inputData("value", "\\d+"));
            root = dataInsert(root, val);
            BSTprettyprint(root, 0);
        } else if (choice == 2) {
            BSTprettyprint(root, 0);
        } else if (choice == 3) {
            if (IsBinarySearchTree(root)) {
                std::cout << "This is BST " << std::endl;
            } else {
                std::cout << "This is NOT BST " << std::endl;
            }
        } else if (choice == 4) {
            int val = std::stoi(inputData("value", "\\d+"));
            root = badDataInsert(root, val);
            BSTprettyprint(root, 0);
        } else {
            std::cout << " Bad choice Retry !! " << std::endl;
        }
    } while (choice != 0);
}
