#include <iostream>
#include <fstream>
#include <sstream>
#include "BST.h"
#include "p3.h"

int main() {
    // Variable to hold the size of the array of numbers to add
    int size;
    string fileName;

    welcome();

    intHeader();
    newLine();

    cout << "** CREATE BST **" << endl;
    BST<int> *intBST = new BST<int>;
    intData(intBST);
    newLine();

    cout << "Enter integer file: ";
    cin >> fileName;
    cout << endl;

    cout << "** TEST INSERT **" << endl;
    readIntFile(fileName, intBST);
    cout << endl;
    intData(intBST);
    newLine();

    cout << "** TEST TRAVERSALS **" << endl;
    intTraversal(intBST);
    newLine();

    cout << "** TEST CONTAINS **" << endl;
    intContains(intBST);
    newLine();

    cout << "** TEST REMOVE **" << endl;
    cout << "Removing in this order: 20 40 10 70 99 -2 59 43" << endl;
    int remNums[] = {20, 40, 10, 70, 99, -2, 59, 43};
    size = 8;
    intRemove(intBST, remNums, size);
    intData(intBST);
    cout << endl;
    intTraversal(intBST);
    newLine();

    cout << "** TEST INSERT (again) **" << endl;
    cout << "Inserting in this order: 20 40 10 70 99 -2 59 43" << endl;
    int newNums2[] = {20, 40, 10, 70, 99, -2, 59, 43};
    intInsert(intBST, newNums2, size);
    intData(intBST);
    cout << endl;
    intTraversal(intBST);
    newLine();

    strHeader();
    newLine();

    cout << "** CREATE BST **" << endl;
    BST<string> *strBST = new BST<string>;
    strData(strBST);
    newLine();

    cout << "Enter string file: ";
    cin >> fileName;
    cout << endl;

    cout << "** TEST INSERT **" << endl;
    readStrFile(fileName, strBST);
    cout << endl;
    strData(strBST);
    newLine();

    cout << "** TEST TRAVERSALS **" << endl;
    strTraversal(strBST);
    newLine();

    cout << "** TEST CONTAINS **" << endl;
    strContains(strBST);
    newLine();

    cout << "** TEST REMOVE **" << endl;
    cout << "Removing in this order: gene mary bea uma yan amy ron opal"
         << endl;
    string remName[] = {"gene", "mary", "bea", "uma", "yan", "amy", "ron",
                        "opal"};
    size = 8;
    strRemove(strBST, remName, size);
    strData(strBST);
    cout << endl;
    strTraversal(strBST);
    newLine();

    cout << "** TEST INSERT (again) **" << endl;
    cout << "Inserting in this order: gene mary bea uma yan amy ron opal" <<
         endl;
    string names2[] = {"gene", "mary", "bea", "uma", "yan", "amy", "ron",
                       "opal"};
    strInsert(strBST, names2, size);
    strData(strBST);
    cout << endl;
    strTraversal(strBST);
    newLine();

    cout << "Goodbye!" << endl;
    return EXIT_SUCCESS;
}

void welcome() {
    cout << "\nWelcome to the Binary Search Tree program. In this program you\n"
            "will be able to upload a file of data and add the contents to a\n"
            "binary search tree. As the data is added to the BST, it will be\n"
            "organized from smallest to largest (left to right respectively).\n"
            "A series of tests will perform to show the number of nodes,\n"
            "leaves, height and return various order types. " << endl << endl;
}

void readIntFile(string file, BST<int> *bst) {
    ifstream inFile;
    string fileNumber;
    int number;

    inFile.open(file);
    cout << "Inserting in this order: ";

    if (inFile) {
        while (getline(inFile, fileNumber)) {
            stringstream n(fileNumber);
            n >> number;
            cout << number << " ";
            bst->add(number);
        }
    }
    inFile.close();
}

void readStrFile(string file, BST<string> *bst) {
    ifstream inFile;
    string names;

    inFile.open(file);
    cout << "Inserting in this order: ";

    if (inFile) {
        while (getline(inFile, names)) {
            cout << names << " ";
            bst->add(names);
        }
    }
    inFile.close();
}

void intHeader() {
    cout << "******************************" << endl;
    cout << "* INTEGER BINARY SEARCH TREE *" << endl;
    cout << "******************************" << endl;
}

void strHeader() {
    cout << "******************************" << endl;
    cout << "* INTEGER BINARY SEARCH TREE *" << endl;
    cout << "******************************" << endl;
}

void newLine() {
    cout << endl << endl;
}

void intData(BST<int> *bst) {
    cout << "# of nodes:   " << bst->size() << endl;
    cout << "# of leaves:   " << bst->getLeafCount() << endl;
    cout << "tree height:   " << bst->getHeight() << endl;
    if (bst->empty()) {
        cout << "tree empty? true";
    } else {
        cout << "tree empty? false";
    }
}

void intTraversal(BST<int> *bst) {
    cout << "pre-order: ";
    bst->getPreOrderTraversal();
    cout << endl;
    cout << "in-order: ";
    bst->getInOrderTraversal();
    cout << endl;
    cout << "post-order:  ";
    bst->getPostOrderTraversal();
    cout << endl;
}

void intInsert(BST<int> *bst, int *num, int size) {
    for (int i = 0; i < size; i++) {
        bst->add(num[i]);
    }
}

void intContains(const BST<int> *bst) {
    // values to test if the bst has
    int contains[] = {20, 40, 10, 70, 99, -2, 59, 43};
    int size = 8;

    for (int i = 0; i < size; i++) {
        cout << "has(" << contains[i] << "):   ";
        if (bst->has(contains[i])) {
            cout << "true" << endl;
        } else {
            cout << "false" << endl;
        }
    }
}

void intRemove(BST<int> *bst, int *num, int size) {
    for (int i = 0; i < size; i++) {
        bst->remove(num[i]);
    }
}

void strData(BST<string> *bst) {
    cout << "# of nodes:   " << bst->size() << endl;
    cout << "# of leaves:   " << bst->getLeafCount() << endl;
    cout << "tree height:   " << bst->getHeight() << endl;
    if (bst->empty()) {
        cout << "tree empty? true";
    } else {
        cout << "tree empty? false";
    }
}

void strTraversal(BST<string> *bst) {
    cout << "pre-order: ";
    bst->getPreOrderTraversal();
    cout << endl;
    cout << "in-order: ";
    bst->getInOrderTraversal();
    cout << endl;
    cout << "post-order:  ";
    bst->getPostOrderTraversal();
    cout << endl;
}

void strInsert(BST<string> *bst, string *str, int size) {
    for (int i = 0; i < size; i++) {
        bst->add(str[i]);
    }
}

void strContains(const BST<string> *bst) {
    // values to test if the bst has
    string contains[] = {"gene", "mary", "bea", "uma", "yan", "amy", "ron",
                         "opal"};
    int size = 8;

    for (int i = 0; i < size; i++) {
        cout << "has(" << contains[i] << "):   ";
        if (bst->has(contains[i])) {
            cout << "true" << endl;
        } else {
            cout << "false" << endl;
        }
    }
}

void strRemove(BST<string> *bst, string *str, int size) {
    for (int i = 0; i < size; i++) {
        bst->remove(str[i]);
    }
}





