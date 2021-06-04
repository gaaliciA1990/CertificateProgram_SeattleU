#include <iostream>
#include <pthread.h>
#include <vector>
#include <cstring>
#include <exception>
#include <sstream>

using namespace std;
//Global Variables
float average = 0;
int minimum = 0, maximum = 0;
vector<int> numbers;

/*
 * NOTE - Cast the void argument to the vector or other variable type in the
 * respective method if  a global variable is not a viable option:
 * vector<int> *numbers = (vector<int> *) numArg;
 */

/**
 * Thread for determining the average of the numbers within a vector
 *
 * @param numArg the argument to be passed through the thread
 * @return a void pointer
 */
void *avgTh(void *numArg) {

    float sum = 0;
    float total = numbers.size();

    for (int i = 0; i < total; i++) {
        sum = sum + numbers.at(i);
    }

    average = sum / total;
    printf("The average value is: %.2f", average);
}

/**
 * Thread for determining the minimum number within a given vector
 *
 * @param numArg the argument to be passed through the thread
 * @return a void pointer
 */
void *minTh(void *numArg) {
    minimum = numbers.at(0);
    for (int i = 1; i < numbers.size(); i++) {
        if (minimum > numbers.at(i)) {
            minimum = numbers.at(i);
        }
    }
    printf("\nThe minimum value is: %d", minimum);
}

/**
 * Thread for determining the maximum number within a given vector
 *
 * @param numArg the argument to be passed through the thread
 * @return a void pointer
 */
void *maxTh(void *numArg) {
    maximum = numbers.at(0);

    for (int i = 1; i < numbers.size(); i++) {
        if (maximum < numbers.at(i)) {
            maximum = numbers.at(i);
        }
    }

    printf("\nThe maximum value is: %d", maximum);
}

/**
 * This will ask the user to provide numbers to be placed in the vector. We
 * will also check to make sure all inputs are valid numbers and ask again if
 * not.
 * @param vect  Vector of numbers to be populated
 * @return the filled vector
 */
void userInput(vector<int> &vect) {
    string input;
    char delimiter = ' ';

    cout << "Enter the list of numbers, separated with a space: ";
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

/**
 * The main method creates the 3 threads and runs them through the respective
 * math operations. This will also call the user input for populating the
 * numbers vector.
 * @return 0 when success, else other numbers
 */
int main() {
    userInput(numbers);

    pthread_t stat1;
    pthread_t stat2;
    pthread_t stat3;

    int error = pthread_create(&stat1, NULL, &avgTh, &numbers);
    if (error) {
        cout << "Thread creation failed for stat1: " << strerror(error) << endl;
        return -1;
    }
    error = pthread_create(&stat2, NULL, &minTh, &numbers);
    if (error) {
        cout << "Thread creation failed for stat2: " << strerror(error) << endl;
        return -1;
    }
    error = pthread_create(&stat3, NULL, &maxTh, &numbers);
    if (error) {
        cout << "Thread creation failed for stat3: " << strerror(error) << endl;
        return -1;
    }

    pthread_join(stat1, NULL);
    pthread_join(stat2, NULL);
    pthread_join(stat3, NULL);

    return 0;
}

