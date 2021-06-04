#include <iostream>
#include <pthread.h>
#include <vector>
#include <cstring>
#include <exception>
#include <sstream>
#include <algorithm>

using namespace std;


vector<int> unsortedVect, sortedVect;


struct splitVectors {
    vector<int> *left;
    vector<int> *right;
};

void printV(vector<int> &vect);

void userInput(vector<int> &vect);

void *sortThread(void *arg);

void *mergeThread(void *arg);

/**
 * Main method for dividing a provided vector from a user and then sorting
 * and merging through 3 threads.
 * @return 0 when success, else other number
 */
int main() {
    userInput(unsortedVect);

    cout << "Elements of the vector: ";
    printV(unsortedVect);

    struct splitVectors args;

    vector<int> left(unsortedVect.begin(),
                     unsortedVect.begin() + unsortedVect.size() / 2);
    vector<int> right(unsortedVect.begin() + unsortedVect.size() / 2,
                      unsortedVect.end());

    cout << "\nNumber of elements = " << unsortedVect.size() << ", half size of"
                                                                " vector = "
         << left.size() << endl;

    args.left = &left;
    args.right = &right;

    pthread_t leftV;
    pthread_t rightV;
    pthread_t mergeThr;

    int error = pthread_create(&leftV, NULL, &sortThread, &left);
    if (error) {
        cout << "Thread creation failed for left sort: " << strerror(error) <<
             endl;
        return -1;
    }
    error = pthread_create(&rightV, NULL, &sortThread, &right);
    if (error) {
        cout << "Thread creation failed for right sort: " << strerror(error) <<
             endl;
        return -1;
    }
    pthread_join(leftV, NULL);
    pthread_join(rightV, NULL);

    error = pthread_create(&mergeThr, NULL, &mergeThread, (void *)
            &args);
    if (error) {
        cout << "Thread creation failed for merging: " << strerror(error) <<
             endl;
        return -1;
    }
    cout << "Sorted Vector: ";
    pthread_join(mergeThr, NULL);
}

/**
 * This method is for printing out the vector values after being created.
 * @param vect
 */
void printV(vector<int> &vect) {
    for (int i = 0; i < vect.size(); i++) {
        std::cout << vect.at(i) << ' ';
    }
}

/**
 * This method sorts the passed through argument vector using sort function.
 * @param arg the arugment passed through the vector
 * @return a void pointer
 */
void *sortThread(void *arg) {
    // cast the void pointer argument to a vector
    vector<int> *vect = (vector<int> *) arg;

    sort(vect->begin(), vect->end());
}

/**
 * This method will merge the two threads into a single sorted vector
 * @param arg the arugment passed through the vector
 * @return a void pointer
 */
void *mergeThread(void *arg) {
    struct splitVectors *vectors = static_cast<splitVectors *>(arg);

    vector<int> *lVector = (vector<int> *) vectors->left;
    vector<int> *rVector = (vector<int> *) vectors->right;

    // siz of the two vectors
    int lSize = lVector->size();
    int rSize = rVector->size();
    // indices for the vectors to traverse
    int i, j;
    i = j = 0;

    while (i < lSize && j < rSize) {
        if (lVector->at(i) <= rVector->at(j)) {
            sortedVect.push_back(lVector->at(i));
            i++;
        } else {
            sortedVect.push_back(rVector->at(j));
            j++;
        }
    }

    while (i < lSize) {
        sortedVect.push_back(lVector->at(i));
        i++;
    }

    while (j < rSize) {
        sortedVect.push_back(rVector->at(j));
        j++;
    }
    printV(sortedVect);
}

/**
 * This will ask the user to provide numbers to be placed in the vector. We
 * will also check to make sure all inputs are valid numbers and ask again if
 * not.
 * @param vect  Vector of numbers to be populated
 */
void userInput(vector<int> &vect) {
    string input;
    char delimiter = ' ';

    cout << "Enter the elements of your vector, separated by a space: ";
    getline(cin, input);
    stringstream check1(input);

    size_t pos = 0;
    string number;
    while (getline(check1, number, delimiter)) {
        try {
            int x = stoi(number);
            vect.push_back(x);
        } catch (const invalid_argument) {
            cerr << "\nInvalid input found. Non-integers ignored: " << number <<
                 endl;
        }
    }
}