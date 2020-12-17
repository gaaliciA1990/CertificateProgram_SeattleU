/**
 * This program will test the functionality of the WordCounter file and run
 * through various tests. It will accept files and read those files into an
 * array of linked lists.
 * @author Alicia Garcia
 * Course CPSC 5910-01
 * 11/16/2020 (Fall Quarter 2020)
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "WordCounter.h"
#include "English.h"

using namespace std;

bool readStrFile(string file, WordCounter *wordTable);

void userWordSearch(vector<string> &words);

void userDataInput(string &file, int &cap);

void printTableStats(WordCounter *wordTable);

void printWordAnalysis(vector<string> words, WordCounter *wordTable);

int main() {
    int capacity = 0;
    char repeat = 'Y';
    string filename;

    do {
        userDataInput(filename, capacity);
        vector<string> searchWord;
        WordCounter *wordCountTable = new WordCounter(capacity);
        if (wordCountTable->empty()) {
            cout << endl;
            cout << "Hash table ready for words!" << endl;
            cout << "Attempting to add words to the table now..." << endl <<
                 endl;
        }

        if (!readStrFile(filename, wordCountTable)) {
            return EXIT_FAILURE;  // end program
        }

        if (!wordCountTable->empty()) {
            cout << "Hash table filled!" << endl << endl;
        } else {
            printTableStats(wordCountTable);
            userWordSearch(searchWord);
            printWordAnalysis(searchWord, wordCountTable);
        }

        cout << "Do you want to analyze another file? (Y/N): ";
        cin >> repeat;
        cout << endl;

        searchWord.clear(); //empty vector
        delete wordCountTable; // delete hash table
    } while (repeat == 'Y' || repeat == 'y');

    return EXIT_SUCCESS;
}

void userDataInput(string &file, int &cap) {
    cout << "What is the filename: ";
    cin >> file;
    cout << "What is the capacity: ";
    cin >> cap;
    string line; // throw away variable to consume line
    getline(cin, line); // consume new line from capacity

}

void userWordSearch(vector<string> &words) {
    string placeHolderWord; // placeholder variable for the read word
    string line;    // holds the line of words

    cout << "Enter the words to analyze (separated by space): ";
    getline(cin, line);
    istringstream iss(line);
    while (iss >> placeHolderWord) {
        words.push_back(placeHolderWord);
    }
}

bool readStrFile(string file, WordCounter *wordTable) {
    fstream inFile;
    string preClean, postClean; // store words pre and post word cleaning

    inFile.open(file.c_str());

    if (!inFile.fail()) {
        while (inFile >> preClean) {
            postClean = English::cleanWord(preClean);
            if (postClean.empty()) {
                continue; // skip empty word strings
            }
            wordTable->addWord(postClean);
        }
        auto commonWords = English::commonWords();  // store words in a vector
        for (int i = 0; i < commonWords.size(); i++) {
            wordTable->remove(commonWords[i]);
        }
    } else {
        cout << "File does not exist. Closing program." << endl;
        inFile.close();
        return false;
    }
    inFile.close();
    return true;
}

void printTableStats(WordCounter *wordTable) {
    cout << "Word counter statistics:" << endl;
    cout << "       Unique Words: " << wordTable->getUniqueWordCount() << endl;
    cout << "       Total Words: " << wordTable->getTotalWordCount() << endl;
    // set the decimal place to 3
    cout << fixed;
    cout << setprecision(3);
    cout << "       Load Factor: " << wordTable->getLoadFactor() << endl;
    cout << endl; //formatting line
}

void printWordAnalysis(vector<string> words, WordCounter *wordTable) {
    cout << "Analysis of words:" << endl;
    for (int i = 0; i < words.size(); i++) {
        cout << "       " << words[i] << ": " << wordTable->getWordCount
                (words[i]) << endl;
    }
}