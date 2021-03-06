#include <iostream>

#include "BinaryTree.h"

using namespace std;

struct Node
{
    int value;
    int height;
    Node *left;
    Node *right;
};

Node *createNode(int value)
{
    Node *newNode = new Node;
    newNode->value = value;
    newNode->height = 0;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

struct BinaryTree
{
    Node *root;
};

int height(Node *node)
{
   return node ? node->height : 0;
}

int balanceFactor(Node *node)
{
    if ((node->left == nullptr || node->right == nullptr) && node->height == 2)
        return (node->left == nullptr) ? -2 : 2;

   return height(node->left) - height(node->right);
}

void updateHeight(Node *node)
{
    if (node->left == nullptr && node->right == nullptr)
        node->height = 0;
    else
    {
        int heightLeft = height(node->left);
        int heightRight = height(node->right);
        node->height = ((heightLeft > heightRight) ? heightLeft : heightRight) + 1;
    }
}

BinaryTree *create()
{
    BinaryTree *newTree = new BinaryTree;
    newTree->root = nullptr;
    return newTree;
}

Node *rotateRight(Node* root)
{
   Node* pivot = root->left;
   root->left = pivot->right;
   pivot->right = root;
   updateHeight(root);
   updateHeight(pivot);
   return pivot;
}

Node *rotateLeft(Node* root)
{
   Node* pivot = root->right;
   root->right = pivot->left;
   pivot->left = root;
   updateHeight(root);
   updateHeight(pivot);
   return pivot;
}

Node* balance(Node* p)
{
    if (p == nullptr)
        return nullptr;

    updateHeight(p);

    if (balanceFactor(p) == 2)
    {
        if (balanceFactor(p->left) < 0)
            p->left = rotateLeft(p->left);

        return rotateRight(p);
    }

    if (balanceFactor(p) == -2)
    {
        if (balanceFactor(p->right) > 0)
            p->right = rotateRight(p->right);

        return rotateLeft(p);
    }

    updateHeight(p);
    return p;
}

Node *addValueToNode(int value, Node *parentNode)
{
    if (parentNode == nullptr)
        return createNode(value);

    if (value < parentNode->value)
    {
        parentNode->left = addValueToNode(value, parentNode->left);
        parentNode = balance(parentNode);
    }
    else if (value > parentNode->value)
    {
        parentNode->right = addValueToNode(value, parentNode->right);
        parentNode = balance(parentNode);
    }

    return parentNode;
}

void addValue(int value, BinaryTree *t)
{
    t->root = addValueToNode(value, t->root);
    t->root = balance(t->root);
}

int deleteMin(Node *parentNode)
{
    Node *temp = parentNode;

    while (temp->left->left != nullptr)
        temp = temp->left;

    int value = temp->left->value;
    Node *toDelete = temp->left;
    temp->left = temp->left->right;
    delete toDelete;
    return value;
}

Node *deleteValueInNode(Node *parentNode, int value)
{
    if (parentNode == nullptr)
        return parentNode;

    if (value < parentNode->value)
        parentNode->left = deleteValueInNode(parentNode->left, value);
    else if (value > parentNode->value)
        parentNode->right = deleteValueInNode(parentNode->right, value);
    else if (parentNode->left != nullptr && parentNode->right != nullptr)
    {
        if (parentNode->right->left == nullptr)
        {
            Node *toDelete = parentNode->right;

            parentNode->value = parentNode->right->value;
            parentNode->right = parentNode->right->right;

            delete toDelete;
        }
        else
        {
            parentNode->value = deleteMin(parentNode->right);
            parentNode->right = balance(parentNode->right);
        }
    }
    else
    {
        Node *toDelete = parentNode;

        if (parentNode->left != nullptr)
            parentNode = parentNode->left;
        else
            parentNode = parentNode->right;

        delete toDelete;
    }

    parentNode = balance(parentNode);
    return parentNode;
}

void deleteValue(int value, BinaryTree *t)
{
    if (t->root == nullptr)
        return;

    t->root = deleteValueInNode(t->root, value);
}

bool contains(int value, BinaryTree *t)
{
    if (t->root == nullptr)
        return false;

    Node *temp = t->root;

    while (temp != nullptr)
    {
        if (temp->value == value)
            return true;
        else if (value < temp->value)
            temp = temp->left;
        else if (value > temp->value)
            temp = temp->right;
    }

    return false;
}

void printNode(PrintMode mode, Node *parentNode)
{
    if (parentNode == nullptr)
    {
        if (mode == structure)
            cout << " null";
        return;
    }

    switch (mode)
    {
        case inAscending:
        {
            if (parentNode->left == nullptr && parentNode->right == nullptr)
                cout << parentNode->value << " ";
            else
            {
                printNode(inAscending, parentNode->left);
                cout << parentNode->value << " ";
                printNode(inAscending, parentNode->right);
                return;
            }
            break;
        }
        case inDescending:
        {
            if (parentNode->left == nullptr && parentNode->right == nullptr)
                cout << parentNode->value << " ";
            else
            {
                printNode(inDescending, parentNode->right);
                cout << parentNode->value << " ";
                printNode(inDescending, parentNode->left);
                return;
            }
            break;
        }
        case structure:
        {
            cout << " (" << parentNode->value;
            printNode(structure, parentNode->left);
            printNode(structure, parentNode->right);
            cout << ")";
            break;
        }
    }
}

void print(PrintMode mode, BinaryTree *t)
{
    if (t->root == nullptr)
        return;

    Node *temp = t->root;

    switch (mode)
    {
        case inAscending:
        {
            if (temp->left == nullptr && temp->right == nullptr)
            {
                cout << temp->value;
                return;
            }
            printNode(inAscending, temp->left);
            cout << temp->value << " ";
            printNode(inAscending, temp->right);
            break;
        }
        case inDescending:
        {
            Node *temp = t->root;

            if (temp->left == nullptr && temp->right == nullptr)
            {
                cout << temp->value << " ";
                return;
            }

            printNode(inDescending, temp->right);
            cout << temp->value << " ";
            printNode(inDescending, temp->left);
            break;
        }
        case structure:
        {
            cout << "(" << temp->value;
            printNode(structure, temp->left);
            printNode(structure, temp->right);
            cout << ")";
            break;
        }
    }
}

void deleteNode(Node *n)
{
    if (n == nullptr)
        return;

    if (n->left == nullptr && n->right == nullptr)
        delete n;
    else
    {
        deleteNode(n->left);
        deleteNode(n->right);
        delete n;
    }
}

void deleteTree(BinaryTree *&t)
{
    if (t->root != nullptr)
    {
        Node *temp = t->root;
        deleteNode(temp->left);
        deleteNode(temp->right);
        delete temp;
    }

    delete t;
    t = nullptr;
}
