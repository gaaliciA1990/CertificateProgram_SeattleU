/*
 * Author: Alicia Garcia
 * Date: 1/8/21
 * Version: 1.0
 */

#include <iostream>

using namespace std;

//Declaring methods prior to main. See methods below main method
int power(int num, int exp);
int myLog(int base, int num);

/**
 * The main method will execute the called methods for testing
 * @return
 */
int main() {
    int num, exp, base;

    // Requesting the users inputs for solving the power/exponent equation
    cout << "Enter a number: ";
    cin >> num;
    cout << "Enter an exponent: ";
    cin >> exp;
    cout << endl; // formatting line

    //TODO: add an input validation to ensure only numbers are entered. Maybe
    // create a loop to ask for the inputs again

    // Return the results of the calculation
    cout << num << " to the power of " << exp << " is  " << power(num, exp);
    cout << endl << endl; // formatting line

    // Requesting the users inputs for solving the log base equation
    cout << "Enter a base: ";
    cin >> base;
    cout << "Enter an number: ";
    cin >> num;
    cout << endl; // formatting line

    // Return the results of the calculation
    cout << "Log of " << num << " in base " << base << " is " << myLog(base,
                                                                       num);
    cout << endl; // formatting line

    return EXIT_SUCCESS;
}

/**
 * The power method returns the result of a number raised to a given power.
 * If the exponent is negative, 0 is returned. If exp = 0, return 1.
 * @param num   The value to be calculated on
 * @param exp   The value the power the number is raised to
 * @return the solution to the calculation
 */
int power(int num, int exp) {
    int result = 1;  // Variable for the result to continue multiplying ints

    if (exp == 0) {
        return 1;
    } else if (exp < 0) {
        return 0;
    } else {
        for (int i = 0; i < exp; i++) {
            result = result * num;
        }
        return result;
    }
}

/**
 * This method will compute the log of a number, rounded down by calling the
 * power method
 * @param base  The log_b base number
 * @param num   The number taken the base of
 * @return  The result of the calculation
 */
int myLog(int base, int num) {
    int result;  // the result of the equation calling power method
    int exp = 0;  // counter variable to test exponents that find our answer

    // run through the power function until one of the conditions is met and
    // return the results of exponent
    while (true) {
        result = power(base, exp);
        if (result == num) {
            return exp;
        }
        else if (result > num) {
            return exp - 1;  // Return the prev exponent, as this is the
                             // correct answer
        }
        exp++;
    }
}

