#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>

using namespace std;

template <typename Type>
class BST_Node
{
public:
    Type key;
    BST_Node *left;
    BST_Node *right;

    BST_Node(Type key)
    {
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
    }
};

template <typename Type>
class BST
{
private:
    // helper function for copy constructor
    BST_Node<Type> *copyTree(BST_Node<Type> *originalNode);
    // helper function for deallocating all nodes recursively
    void clearTree(BST_Node<Type> *node);
    // insertRecursive is helper function for insert
    void insertRecursive(BST_Node<Type> *node, Type key);
    // deleteRecursive is helper function for deleteNode
    BST_Node<Type> *deleteRecursive(BST_Node<Type> *node, Type key);
    // Helper method to find the minimum value in the subtree rooted at node (as well as the node itself)
    Type minValue(BST_Node<Type> *node);
    // Helper function for recursively searching for a key
    bool findHelper(BST_Node<Type> *node, Type lkpkey);
    // Helper function for recursively adding the in-order output key values to a string s
    void printTreeInOrderHelper(BST_Node<Type> *node, string &s);

public:
    BST_Node<Type> *root;
    // Constructor
    BST();

    // Copy Constructor
    BST(const BST &other);

    // Copy Assignment Operator - uses helper functions copyTree and clearTree
    BST &operator=(const BST &other);

    // Destructor
    ~BST();

    // Insert method to insert node with key
    void insert(Type key);

    // deleteNode method to delete a node with a particular key
    void deleteNode(Type key);

    // Find method to search for a key; returns true if it exists in the tree and false if it does not
    bool find(Type lkpkey);

    // Creates and returns a string that contains the tree in-order
    string printTreeInOrder();
};

template <typename Type>
BST<Type>::BST()
{
    this->root = nullptr;
}

template <typename Type>
BST_Node<Type> *BST<Type>::copyTree(BST_Node<Type> *originalNode)
{
    if(originalNode == nullptr){
        return nullptr;
    }
    BST_Node<Type>* newRoot = new BST_Node<Type>(originalNode->key);
    newRoot->left = copyTree(originalNode->left);
    newRoot->right = copyTree(originalNode->right);
    return newRoot;
}

template <typename Type>
BST<Type>::BST(const BST<Type> &other)
{
    this->root = copyTree(other.root);
}

template <typename Type>
BST<Type> &BST<Type>::operator=(const BST &other)
{
    if(this != &other){
        clearTree(root);
        root = copyTree(other.root);
    }
    return *this;
}

template <typename Type>
void BST<Type>::clearTree(BST_Node<Type> *node)
{
    if(node != nullptr){
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}

template <typename Type>
BST<Type>::~BST()
{
    clearTree(root);
}

template <typename Type>
void BST<Type>::insertRecursive(BST_Node<Type> *node, Type key)
{
    // check if the current node is bigger than the key (starting at root).
    // if it's greater, move to the right subtree
    // if it's less, move to the left subtree
    if (node->key > key)
    {
        if (node->left == nullptr)
        {
            // if the left subtree doesn't exist, u found the place to insert
            node->left = new BST_Node<Type>(key);
        }
        else
        {
            // if it does, then u have to keep going
            insertRecursive(node->left, key);
        }
    }
    else if (node->key < key)
    {
        if (node->right == nullptr)
        {
            // if the right subtree doesn't exist, u found the place to insert
            node->right = new BST_Node<Type>(key);
        }
        else
        {
            // if it does, then u have to keep going
            insertRecursive(node->right, key);
        }
    }
}

template <typename Type>
void BST<Type>::insert(Type key)
{
    if (this->root == nullptr)
    {
        this->root = new BST_Node<Type>(key);
    }
    else
    {
        insertRecursive(this->root, key);
    }
}

template <typename Type>
BST_Node<Type> *BST<Type>::deleteRecursive(BST_Node<Type> *node, Type key)
{
    if(node == nullptr){
        return nullptr;
    }
    if (key > node->key)
    {
        node->right = deleteRecursive(node->right, key);
    }
    else if (key < node->key)
    {
        node->left = deleteRecursive(node->left, key);
    }
    else
    {
        // 1st case: only one child
        //only right child
        if (node->left == nullptr)
        {
            BST_Node<Type>* temp = node->right;
            delete node;
            return temp;
        }
        //only left child
        else if (node->right == nullptr)
        {
            BST_Node<Type>* temp = node->left;
            delete node;
            return temp;
        }
        //has both children, find the smallest in the right tree
        else{
            node->key = minValue(node->right);
            node->right = deleteRecursive(node->right, node->key);
        }
    }
    return node;
}

template <typename Type>
void BST<Type>::deleteNode(Type key)
{
    if (this->root == nullptr)
    {
        return;
    }
    this->root = deleteRecursive(this->root, key);
}

// Helper method to find the minimum value in the subtree rooted at a particular node (including the node itself)
template <typename Type>
Type BST<Type>::minValue(BST_Node<Type> *node)
{
    BST_Node<Type> *curr = node;
    while (curr->left != nullptr)
    {
        curr = curr->left;
    }
    return curr->key;
}

template <typename Type>
bool BST<Type>::findHelper(BST_Node<Type> *node, Type lkpkey)
{
    if (node == nullptr)
    {
        return false;
    }
    if (node->key == lkpkey)
    {
        return true;
    }
    else if (lkpkey < node->key)
    {
        return findHelper(node->left, lkpkey);
    }
    else if (lkpkey > node->key)
    {
        return findHelper(node->right, lkpkey);
    }
}

template <typename Type>
bool BST<Type>::find(Type lpkey)
{
    if (this->root == nullptr)
    {
        return false;
    }
    return findHelper(this->root, lpkey);
}

template <typename Type>
void BST<Type>::printTreeInOrderHelper(BST_Node<Type> *node, string &s)
{
    // end the recursive calls if you reach the furthest left or right
    if (node == nullptr)
        return;
    printTreeInOrderHelper(node->left, s);
    s += to_string(node->key) + " ";
    printTreeInOrderHelper(node->right, s);
}

template <typename Type>
string BST<Type>::printTreeInOrder()
{
    if (this->root == nullptr)
    {
        return "";
    }
    string s = "";
    printTreeInOrderHelper(this->root, s);
    return s;
}

#endif
