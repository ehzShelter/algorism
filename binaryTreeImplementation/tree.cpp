#include <iostream>
#include <cassert>

typedef struct binaryNodeTree {
    int data;
    struct binaryNodeTree* leftChild;
    struct binaryNodeTree* rightChild;
} node;

node* root = NULL;

node* GetNewNode(int data);
void deleteWholeTree(node* root);
void inOrderTraverse(node* root);
void postOrderTraverse(node* root);
void preOrderTraverse(node* root);
int treeSize(node* root);
int treeDepth(node* root);
bool Search(node* root, int data);
node* Insert(node* root, int data);

int main(void)
{
    root = Insert(root, 7);
    root = Insert(root, 12);
    root = Insert(root, 5);
    root = Insert(root, 6);
    root = Insert(root, 2);
    root = Insert(root, 3);
    root = Insert(root, 1);
    root = Insert(root, 11);
    root = Insert(root, 13);
    root = Insert(root, 20);
    root = Insert(root, 25);
    root = Insert(root, 21);
    root = Insert(root, 19);
    root = Insert(root, 22);

    std::cout << "Enter number be searched: ";
    int number = 0;
    std::cin >> number;

    if (Search(root, number)) {
        std::cout << "Found\n";
    }
    else {
        std::cout << "Not Found\n";
    }

    int BitreeSize = treeSize(root);
    std::cout << "Tree Size: " << BitreeSize << std::endl;

    int depth = treeDepth(root);
    std::cout << "Tree depth: " << depth << std::endl;

    std::cout << "\nINORDER   >>> ";
    inOrderTraverse(root);
    std::cout << "\nPREORDER  >>> ";
    preOrderTraverse(root);
    std::cout << "\nPOSTORDER >>> ";
    postOrderTraverse(root);
    std::cout << std::endl;

    deleteWholeTree(root);
}

node* GetNewNode(int data)
{
    node* newNode = new (node);
    // Performs compile-time assertion checking
    assert(newNode);
    newNode->data = data;
    newNode->leftChild = newNode->rightChild = NULL;
    return newNode;
}

node* Insert(node* root, int data)
{
    if (root == NULL) {
        root = GetNewNode(data);
    }
    // if data to be inserted is lesser(equal), insert in leftChild subtree.
    else if (data <= root->data) {
        root->leftChild = Insert(root->leftChild, data);
    }
    // else, insert in rightChild subtree.
    else {
        root->rightChild = Insert(root->rightChild, data);
    }
    return root;
}

bool Search(node* root, int data)
{
    if (root == NULL) {
        return false;
    }
    else if (root->data == data) {
        return true;
    }
    else if (data <= root->data) {
        return Search(root->leftChild, data);
    }
    else {
        return Search(root->rightChild, data);
    }
}

int treeDepth(node* root)
{
    if (root == NULL) {
        return -1;
    }
    else {
        int lh = treeDepth(root->leftChild);
        int rh = treeDepth(root->rightChild);
        return 1 + (lh > rh ? lh : rh);
    }
}

void preOrderTraverse(node* root)
{
    if (root == NULL) {
        return;
    }
    std::cout << root->data << " ";
    preOrderTraverse(root->leftChild);
    preOrderTraverse(root->rightChild);
}

void postOrderTraverse(node* root)
{
    if (root == NULL) {
        return;
    }
    postOrderTraverse(root->leftChild);
    postOrderTraverse(root->rightChild);
    std::cout << root->data << " ";
}

void inOrderTraverse(node* root)
{
    if (root == NULL) {
        return;
    }
    inOrderTraverse(root->leftChild);
    std::cout << root->data << " ";
    inOrderTraverse(root->rightChild);
}

void deleteWholeTree(node* root)
{
    node* current = root;
    if (current == NULL) {
        return;
    }

    deleteWholeTree(current->leftChild);
    deleteWholeTree(current->rightChild);

    delete current;
    current = NULL; // neccessary to make that current pointer null
}

int treeSize(node* root)
{
    if (root == NULL) {
        return 0;
    }
    else {
        return 1 + treeSize(root->leftChild) + treeSize(root->rightChild);
    }
}
