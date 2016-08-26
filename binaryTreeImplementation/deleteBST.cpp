#include <iostream>
#include <queue>
#include <cassert>
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
node* dataDelete(node* root, int data);
node* findMin(node* root);
void BSTprettyprint(node* root, int pos);
bool validate(const std::string& data, const std::string& expression);
std::string inputData(const std::string& fieldName, const std::string& expression);
void levelOrderTraversal(node* root);
void deleteWholeTree(node* root);

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

node* findMin(node* root)
{
    if (root->leftChild == nullptr) {
        return root;
    }
    else {
        return findMin(root->leftChild);
    }
}

// Algorithm is taken from www.mycodeschool.com
node* dataDelete(node* root, int data)
{
    if (root == nullptr) {
        return root;
    }
    else if (data < root->data) {
        root->leftChild = dataDelete(root->leftChild, data);
    }
    else if (data > root->data) {
        root->rightChild = dataDelete(root->rightChild, data);
    }
    // Wohoo... I found you, Get ready to be deleted
    else {
        // Case 1:  No child
        if (root->leftChild == nullptr && root->rightChild == nullptr) {
            delete root;
            root = nullptr;
        }
        // Case 2: -->> One child when leftChild is NIL
        else if (root->leftChild == nullptr) {
            node* hold = root;
            root = root->rightChild;
            delete hold;
        }
        // Case 3: -->> One child when rightChild is NIL
        else if (root->rightChild == nullptr) {
            node* hold = root;
            root = root->leftChild;
            delete hold;
        }
        // case 3: 2 children left or right vertex is not NIL
        // (root->leftChild != nullptr && root->rightChild != nullptr)

        // Algorithm :
        // >>>>Find minimum in right subtree
        // Think about it....That makes sense ...That will balance the BST
        // >>>>copy the value in targetted node
        // >>>>delete duplicate from right subtree
        // VICE VERSA (Algorithm):
        // >>>>Find maximum in left subtree
        // >>>>copy the value in targetted node
        // >>>>delete duplicate from left subtree
        else {
            node* hold = findMin(root->rightChild);
            root->data = hold->data;
            root->rightChild = dataDelete(root->rightChild, hold->data);
        }
    }
    return root;
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

std::string inputData(const std::string& fieldName, const std::string& expression)
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

void levelOrderTraversal(node* root)
{
    if (root == nullptr) {
        return;
    }

    std::queue<node*> Q;
    Q.push(root);

    while (!Q.empty()) {
        node* current = Q.front();
        // front element is popped
        Q.pop();

        std::cout << current->data << " ";
        if (current->leftChild != nullptr) {
            Q.push(current->leftChild);
        }
        if (current->rightChild != nullptr) {
            Q.push(current->rightChild);
        }
    }
    std::cout << std::endl;
}

void appRun(void)
{
    int choice;
    do {
        std::cout << "\nMENU\n\n"
                  << "1 - insertData\n"
                  << "2 - deleteData\n"
                  << "3 - prettyPrint\n"
                  << "4 - levelOrder\n"
                  << "0 - quit\n\n";

        choice = std::stoi(inputData("choice", "\\d+"));

        if (choice == 0) {
            std::cout << "Programm quits\n";
        } else if (choice == 1) {
            int val = std::stoi(inputData("value", "\\d+"));
            root = dataInsert(root, val);
            BSTprettyprint(root, 0);
        } else if (choice == 2) {
            int whichData = std::stoi(inputData("whichData", "\\d+"));
            root = dataDelete(root, whichData);
            BSTprettyprint(root, 0);
        } else if (choice == 3) {
            BSTprettyprint(root, 0);
        } else if (choice == 4) {
            levelOrderTraversal(root);
        } else {
            std::cout << " Bad choice Retry !! " << std::endl;
        }
    } while (choice != 0);
}
