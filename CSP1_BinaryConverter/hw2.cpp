/**
 * Author: Alicia Garcia
 * Version: 1.0
 * Date: 1/23/2021 15:28
 * Class: Seattle University CPSC 5041-02
 * This is free and unencumbered software released into the public domain
 */

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

void greetingMsg();
void goodbyeMsg();
string baseConversion(int base, int decimalNum);
string readVector(vector<int> vector);
int validateUserInput(const string &str);
bool repeat();

/**
 * The main method will implement the base conversion for any given whole
 * number. The user can repeat the program as many times as they want.
 * @return  exit success message for successful exit
 */
int main() {
    int base, decimalNum;
    string answer, number = "decimal number", baseString = "base";

    greetingMsg();
    while (true) {
        decimalNum = validateUserInput(number);
        base = validateUserInput(baseString);

        answer = baseConversion(base, decimalNum);

        cout << "\n" << decimalNum << " converted to base " << base << " = " <<
             answer << endl;
        if (repeat()) {
            continue;
        }
        goodbyeMsg();
        return EXIT_SUCCESS;
    }
}

/**
 * This method will convert a whole number to any base given by the user.
 * @param base  The user's desired base to convert to
 * @param decimalNum    The user's number to convert
 * @return the answer after conversion in a string
 */
string baseConversion(int base, int decimalNum) {
    vector<int> answer;
    int remainder;
    int num = decimalNum;

    while (num >= base) {
        remainder = num % base;
        num = num / base;
        answer.push_back(remainder);
    }
    answer.push_back(num);
    return readVector(answer);
}

/**
 * Simple greeting message to explain the program and parameters
 */
void greetingMsg() {
    cout << "\nWelcome to the Base Converter! This tool will allow you to\n"
            "convert any decimal number to a given base. Ensure the numbers\n"
            "provided are greater than 0 and whole numbers!" << endl << endl;
}

/**
 * This method will ask for the user's inputs, validate the inputs are int
 * and whole numbers.
 * @param str   The string to indicate which value is requested
 * @return  The user input after validation passed
 */
int validateUserInput(const string &str) {
    float number;

    while (true) {
        cout << "Enter a " << str << " to covert: ";
        cin >> number;
        if (cin.fail() || number <= 0 || int(number) != number) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Invalid number entered! Enter a whole number "
                    "that's greater than 0." << endl;
            continue;
        }
        return int(number);
    }
}

/**
 * This method asks the user if they want to replay the program.
 * @return true if the answer is yes, else false
 */
bool repeat() {
    string playAgain;
    while (true) {
        cout << "\nConvert another number? (Y/N) ";
        cin >> playAgain;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Answer not recognized, try again!" << endl;
            continue;
        }
        if (playAgain == "Y" || playAgain == "y" || playAgain == "yes") {
            return true;
        } else if (playAgain == "N" || playAgain == "n" || playAgain ==
                                                           "no") {
            return false;
        } else {
            cout << "Answer not recognized, try again!" << endl;
            continue;
        }
    }
}

/**
 * This help method will read the vector of stored values and convert them to
 * a string, so we can show the answer to the user
 * @param vector The vector holding the base conversion values
 * @return       The answer in string format
 */
string readVector(vector<int> vector) {
    string result;
    int vecNum;
    int size = vector.size();

    for (int i = 0; i < size; i++) {
        vecNum = vector.back();
        vector.pop_back();
        result = result.append(to_string(vecNum));
    }
    return result;
}

void goodbyeMsg() {
    cout << "Thanks for using the Base Converter. Have a nice day!" <<
    endl;
}