//
// Created by garci on 10/21/2020.
//

#ifndef P3_BST_P3_H
#define P3_BST_P3_H

using namespace std;

/**
 * Welcome message explaining the program
 */
void welcome();

/**
 * Requests the integer file, reads the file and prints the order the values
 * will be added to the BST while populating the BST.
 * @param file The user inputted file
 * @param bst The tree to be populated
 */
void readIntFile(string file, BST<int> *bst);

/**
 * Requests the string file, reads the file and prints the order the values
 * will be added to the BST while populating the BST.
 * @param file The user inputted file
 * @param bst The tree to be populated
 */
void readStrFile(string file, BST<string> *bst);

/**
 * Integer test header
 */
void intHeader();

/**
 * String test header
 */
void strHeader();

/**
 * Will print two new lines for easier formatting
 */
void newLine();

/**
 * This will print the data relating to the size of the BST
 * @param bst The integer tree
 */
void intData(BST<int> *bst);

/**
 * This will insert new numbers from an array into the BST
 * @param bst The target BST
 * @param num The point reference for the value to add
 * @param size The total size of the array
 */
void intInsert(BST<int> *bst, int *num, int size);

/**
 * This will execute the traverals methods and print the values
 * @param bst The tree to print from
 */
void intTraversal(BST<int> *bst);

/**
 * This tests the has function and will test against an array of numbers.
 * @param bst The tree to test against
 */
void intContains(const BST<int> *bst);

/**
 * This will remove values from the tree
 * @param bst  The target tree to remove from
 * @param num The point reference for the value to remove
 * @param size The size of the array
 */
void intRemove(BST<int> *bst, int *num, int size);

/**
 * This will print the data relating to the size of the BST
 * @param bst The integer tree
 */
void strData(BST<string> *bst);

/**
 * This will execute the traverals methods and print the values
 * @param bst The tree to print from
 */
void strTraversal(BST<string> *bst);

/**
 * This will insert new name from an array into the BST
 * @param bst The target BST
 * @param str The point reference for the value to add
 * @param size The total size of the array
 */
void strInsert(BST<string> *bst, string *str, int size);

/**
 * This tests the has function and will test against an array of names.
 * @param bst The tree to test against
 */
void strContains(const BST<string> *bst);

/**
 * This will remove values from the tree
 * @param bst  The target tree to remove from
 * @param str The point reference for the value to remove
 * @param size The size of the array
 */
void strRemove(BST<string> *bst, string *str, int size);

#endif //P3_BST_P3_H
