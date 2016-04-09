/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <math.h>

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    Node* temp = t->right;
    t->right = temp->left;
    temp->left = t;
    t = temp; 

}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    Node* temp = t->left;
    t->left = temp->right;
    temp->right = t;
    t = temp; 
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    rotateLeft(t->right);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    int balance = subtree->right->height - subtree->left->height;
    if(balance>1)
    {
        if(subtree->right->height>1)
            rotateLeft(subtree);
        else
            rotateRightLeft(subtree);
    subtree.height = max(subtree->right->height, subtree->left->height) +1;   
    }
    else if(balance<-1)
    {
        if(subtree->left->height<-1)
            rotateRight(subtree);
        else
            rotateLeftRight(subtree);

    subtree.height = max(subtree->right->height, subtree->left->height) +1;
    }
    else 
        subtree.height = max(subtree->right->height, subtree->left->height) +1;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL)   // base case
    {
        subtree = new Node(key, value);
        rebalance(root);
    }      
    if(key < subtree->key) 
        insert(subtree->left,key,value);
    else if (key > subtree->key)
        insert(subtree->right,key,value);   
    else return;
        
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            noChildRemoval(subtree);
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            twoChildRemoval(subtree);
        } else {
            /* one-child remove */
            // your code here
            oneChildRemoval(subtree);
        }
        // your code here
        rebalance(root);
    }
}

template <class K, class V>
void AVLTree<K, V>::oneChildRemoval(Node*& subtree)
{
    if(subtree->right != NULL && subtree->left == NULL)
    {
        Node* temp = subtree;
        subtree = subtree->right;
        delete temp;
        temp = NULL;
    }
    else
    {
        Node* temp = subtree;
        subtree = subtree->left;
        delete temp;
        temp = NULL;
    }   
}

template <class K, class V>
void AVLTree<K, V>::twoChildRemoval(Node*& subtree)
{
    Node* & iop = rightMostChild(subtree->left);
    swap(iop, subtree);
    if(iop->left == NULL)
    {
        delete iop;
        iop = NULL;
    }
    else
        oneChildRemoval(iop);
}

template <class K, class V>
void AVLTree<K, V>::rightMostChild(Node* &subtree)
{
    if(subtree == NULL)
        return;
    while(subtree->right != NULL)
        subtree = subtree->right;

}

template <class K, class V>
void AVLTree<K, V>::noChildRemoval(Node*& subtree)
{
    delete subtree;
    subtree = NULL;
}