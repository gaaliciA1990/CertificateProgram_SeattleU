//
// Created by garci on 10/19/2020.
//

#ifndef P3_BST_BST_H
#define P3_BST_BST_H

#pragma once

#include <stdexcept>
#include <string>

/**
 * This class is a template class for the Binary Search Tree, which will be
 * able to accept any data type.
 * @param T the data type of the BST value.
 */
template<typename T>
class BST {
public:
    /**
     * Simple constructor created an empty BST.
     */
    BST();

    /**
     * Destructor
     */
    ~BST();

    /**
     * Copy constructor creates a copy of the BST.
     * @param other The BST reference to copy
     */
    BST(const BST &other);

    /**
     * Assignment operator. Creates a deep copy of the BST object.
     * @param rhs The BST reference to copy.
     * @return *this
     */
    BST &operator=(const BST &rhs);

    /**
     * Determines if the given key exists in the BST set.
     * @param key Element to search for.
     * @return true if the key is found, else false.
     */
    bool has(T key) const;

    /**
     * Insert a new element into the set. If the element was already in the
     * set, this method will do nothing
     * @param newKey The element to be added.
     */
    void add(T newKey);

    /**
     * Remove the given key from the BST.
     * It is irrelevant how many times this key has been added to the set
     * or even if it is currently an element or not.
     * @param key   The element to be removed.
     */
    void remove(T key);

    /**
     * Checks if the root is null.
     * @return true if null, else false.
     */
    bool empty() const;

    /**
     * This will check to see how many elements are in the BST.
     * @return the size of the BST.
     */
    int size() const;

    /**
     * This will check to see how many leaves are present in the BST.
     * @return the count of leaves in the BST.
     */
    int getLeafCount();

    /**
     * This will check to see how many levels exist within the BST.
     * @return the number of levels.
     */
    int getHeight();

    /**
     * This will traverse the BST and return the elements In Order for a BST.
     * @return the elements of the BST.
     */
    void getInOrderTraversal();

    /**
     * This will traverse the BST and return the elements in Pre Order
     * @return the elements of the BST
     */
    void getPreOrderTraversal();

    /**
     * This will traverse the BST and return the elements in Post Order
     * @return the elements of the BST
     */
    void getPostOrderTraversal();

private:
    struct Node {
        T key;
        Node *left, *right;

        // Convenience constructor
        Node(T newKey, Node *lside = nullptr, Node *rside = nullptr) {
            key = newKey;
            left = lside;
            right = rside;
        }

        /**
        * Find the maximum node's value.
        *
        * @return  key of the right-most node in this subtree
        */
        T findMax() const;

        /**
         * Checks if the node is a leaf (left and right = null)
         * @return true if leaf, else false
         */
        bool isLeaf() const;
    };

    /**
     * The root of the binary search tree.
     */
    Node *root;

    /**
    * Recursive helper method for has.
    * @param rootlet   sub-IntBST in which to look for key
    * @param key  key to search for
    * @return     true if found, false otherwise
    */
    bool has(Node *rootlet, T key) const;

    /**
    * Recursive helper method for add.
    * @param rootlet      sub-IntBST to which to add key
    * @param newKey  key to add
    * @return        rootlet, or if rootlet is nullptr, the new Node with newKey
    */
    Node *add(Node *rootlet, T newKey);

    /**
     * Recursive helper method for remove.
     * @param rootlet   sub-IntBST from which to remove key
     * @param key  key to remove
     * @return     rootlet, or my replacement if I get deleted (could be nullptr
     *             if I'm it and also a leaf)
     */
    Node *remove(Node *rootlet, T key);

    /**
     * Recursive helper method to delete a subtree.
     * @param   rootlet the root of the subtree to delete
     */
    void clear(Node *rootlet);

    /**
     * Recursive helper method to copy a subtree.
     * @param rootlet the root of the subtree to copy
     * @return   a fresh copy of the subtree
     */
    Node *copy(Node *rootlet);

    /**
     * Recursive helper method for the size of the subtree.
     * @param rootlet   the root of the subtree
     * @return  the count of nodes
     */
    int size(Node *rootlet) const;

    /**
     * Recursive helper method for returning the count of leaves in the tree.
     * @param rootlet   the root of the subtree
     * @return  the count of the leaves
     */
    int getLeafCount(Node *rootlet) const;

    /**
     * Recursive helper method for returning the count of levels in the tree
     * @param rootlet   the root of the subtree
     * @return count of levels (height)
     */
    int getHeight(Node *rootlet, int height) const;

    /**
     * Recursive helper method for returning the elements Inorder
     * @param rootlet the root of the subtree
     * @return the values printed
     */
    void getInOrderTraversal(Node *rootlet) const;

    /**
     * Recursive helper method for returning the elements Preorder
     * @param rootlet the root of the subtree
     * @return
     */
    void getPreOrderTraversal(Node *rootlet) const;

    /**
     * Recursive helper method for returning the elements Postorder
     * @param rootlet the root of the subtree
     * @return
     */
    void getPostOrderTraversal(Node *rootlet) const;
};

template<typename T>
BST<T>::BST() {
    root = nullptr;
}

template<typename T>
BST<T>::~BST() {
    clear(root);
}

template<typename T>
BST<T>::BST(const BST &other) {
    root = copy(other.root);
}

template<typename T>
BST<T> &BST<T>::operator=(const BST &rhs) {
    if (this != rhs) {
        clear(root);
        root = copy(rhs.root);
    }
    return *this;
}

template<typename T>
bool BST<T>::has(T key) const {
    return has(root, key);
}

template<typename T>
void BST<T>::add(T newKey) {
    root = add(root, newKey);
}

template<typename T>
void BST<T>::remove(T key) {
    root = remove(root, key);
}

template<typename T>
bool BST<T>::empty() const {
    return root == nullptr;
}

template<typename T>
int BST<T>::size() const {
    return size(root);
}

template<typename T>
int BST<T>::getLeafCount() {
    if (empty()) {
        return 0;
    }
    return getLeafCount(root);
}

template<typename T>
int BST<T>::getHeight() {
    int height = 1;

    if (empty()) {
        return 0;
    }
    return getHeight(root, height);
}

template<typename T>
void BST<T>::getInOrderTraversal() {
    getInOrderTraversal(root);
}

template<typename T>
void BST<T>::getPreOrderTraversal() {
    getPreOrderTraversal(root);
}

template<typename T>
void BST<T>::getPostOrderTraversal() {
    getPostOrderTraversal(root);
}

template<typename T>
T BST<T>::Node::findMax() const {
    if (right == nullptr) {
        return this->key;
    } else {
        return right->findMax();
    }
}

template<typename T>
bool BST<T>::Node::isLeaf() const {
    return (right == nullptr && left == nullptr);
}

template<typename T>
bool BST<T>::has(BST::Node *rootlet, T key) const {
    if (rootlet == nullptr) {
        return false; // not found
    }
    if (key < rootlet->key) {
        return has(rootlet->left, key);
    } else if (key > rootlet->key) {
        return has(rootlet->right, key);
    } else {
        // key == rootlet->key
        return true;
    }
}

template<typename T>
typename BST<T>::Node *BST<T>::add(BST::Node *rootlet, T newKey) {
    if (rootlet == nullptr) {
        rootlet = new Node(newKey);
    } else if (newKey < rootlet->key) {
        rootlet->left = add(rootlet->left, newKey);
    } else if (newKey > rootlet->key) {
        rootlet->right = add(rootlet->right, newKey);
    }
    // else do nothing since newKey is already in the set
    return rootlet;
}

template<typename T>
typename BST<T>::Node *BST<T>::remove(BST::Node *rootlet, T key) {
    if (rootlet == nullptr) {
        return nullptr; // key is not in the IntBST so nothing to do nothing
    }
    if (key < rootlet->key) {
        // recurse down the left, possibly changing its root
        rootlet->left = remove(rootlet->left, key);
        return rootlet;  // no change to rootlet

    } else if (key > rootlet->key) {
        // recurse down the right, possibly changing its root
        rootlet->right = remove(rootlet->right, key);
        return rootlet;  // no change to rootlet

    } else {
        // FOUND IT. key == rootlet.key, so remove this one
        if (rootlet->left == nullptr) {
            //Elevate the subtree to replace "rootlet" and delete rootlet, too
            Node *myReplacement = rootlet->right;
            delete rootlet;
            return myReplacement;

        } else if (rootlet->right == nullptr) {
            //Elevate the left subtree to replace "rootlet" and then delete "rootlet", too
            Node *myReplacement = rootlet->left;
            delete rootlet;
            return myReplacement;

        } else {
            // Swap with predecessor node which is the max value from left
            rootlet->key = rootlet->left->findMax();
            // and then remove the node that had the predecessor
            rootlet->left = remove(rootlet->left, rootlet->key);
            return rootlet;
        }
    }
}

template<typename T>
void BST<T>::clear(BST::Node *rootlet) {
    if (rootlet != nullptr) {
        clear(rootlet->left);
        clear(rootlet->right);
        delete rootlet;
    }
}

template<typename T>
typename BST<T>::Node *BST<T>::copy(BST::Node *rootlet) {
    if (rootlet == nullptr) {
        return nullptr; // do nothing
    } else {
        return new Node(rootlet->key, copy(rootlet->left), copy
                (rootlet->right));
    }
}

template<typename T>
int BST<T>::size(BST::Node *rootlet) const {
    int count = 0;
    // base case
    if (rootlet == nullptr) {
        return count;
    }
    count++;
    if (rootlet->right != nullptr) {
        count += size(rootlet->right);
    }
    if (rootlet->left != nullptr) {
        count += size(rootlet->left);
    }
    return count;
}

template<typename T>
int BST<T>::getLeafCount(BST::Node *rootlet) const {
    int count = 0;

    if (rootlet->isLeaf()) {
        count++;
    } else {
        if (rootlet->left != nullptr) {
            count += getLeafCount(rootlet->left);
        }
        if (rootlet->right != nullptr) {
            count += getLeafCount(rootlet->right);
        }
    }
    return count;
}

template<typename T>
int BST<T>::getHeight(BST::Node *rootlet, int height) const {
    int depthR = 0, depthL = 0;

    if (rootlet->isLeaf()) {
        return height;
    }
    height++;
    if (rootlet->right != nullptr) {
        depthR = getHeight(rootlet->right, height);
    }
    if (rootlet->left != nullptr) {
        depthL = getHeight(rootlet->left, height);
    }
    if (depthL > depthR) {
        return depthL;
    } else if (depthR > depthL) {
        return depthR;
    }
        // if they're equal, it doesn't matter which we return
    else {
        return depthL;
    }
}

template<typename T>
void BST<T>::getInOrderTraversal(BST::Node *rootlet) const {
    if (rootlet == nullptr) {
        return;
    }
    getInOrderTraversal(rootlet->left);
    std::cout << rootlet->key << " ";
    getInOrderTraversal(rootlet->right);
}

template<typename T>
void BST<T>::getPreOrderTraversal(BST::Node *rootlet) const {
    if (rootlet == nullptr) {
        return;
    }
    std::cout << rootlet->key << " ";
    getPreOrderTraversal(rootlet->left);
    getPreOrderTraversal(rootlet->right);
}

template<typename T>
void BST<T>::getPostOrderTraversal(BST::Node *rootlet) const {
    if (rootlet == nullptr) {
        return;
    }
    getInOrderTraversal(rootlet->left);
    getInOrderTraversal(rootlet->right);

    std::cout << rootlet->key << " ";
}


#endif //P3_BST_BST_H
