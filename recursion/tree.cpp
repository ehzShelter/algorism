#include <iostream>
#include <cassert>

typedef struct binaryNodeTree {
    int data;
    struct binaryNodeTree* leftChild;
    struct binaryNodeTree* rightChild;
} node;

node* root = NULL;

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

int main(void)
{
    root = Insert(root, 15);
    root = Insert(root, 10);
    root = Insert(root, 20);
    root = Insert(root, 25);
    root = Insert(root, 81);
    root = Insert(root, 12);
    root = Insert(root, 202);
    root = Insert(root, 88);
    root = Insert(root, 14);
    root = Insert(root, 21);
    root = Insert(root, 85);
    root = Insert(root, 19);

    std::cout << "Enter number be searched: ";
    int number = 0;
    std::cin >> number;

    if (Search(root, number)) {
        std::cout << "Found\n";
    }
    else {
        std::cout << "Not Found\n";
    }

    std::cout << "Tree depth: " << treeDepth(root) << std::endl;

    std::cout << "\nINORDER   >>> ";
    inOrderTraverse(root);
    std::cout << "\nPREORDER  >>> ";
    preOrderTraverse(root);
    std::cout << "\nPOSTORDER >>> ";
    postOrderTraverse(root);
    std::cout << std::endl;

    deleteWholeTree(root);
}

