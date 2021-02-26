/**
 * This is a hashing word counter program that will track unique counts for
 * unique words, as well as total unique words and total words per text file.
 * @author Alicia Garcia
 * Course CPSC 5910-01
 * 11/16/2020 (Fall Quarter 2020)
 */

#ifndef P5_HASHING_WORDCOUNTER_H
#define P5_HASHING_WORDCOUNTER_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include "LinkedList.h"

/**
 *
 */
class WordCounter {
public:
    /**
     * Constructor
     * @param cap The distinctWordcount of the array
     */
    WordCounter(int cap);

    /**
     * Destructor
     */
    ~WordCounter();

    /**
     * Copy constructor
     * @param other another WordCounter to copy
     */
    WordCounter(const WordCounter &other);

    /**
     * Assignment operator
     * @param rhs another WordCounter to copy (right hand side of the =
     *                      expression)
     * @return *this
     */
    WordCounter &operator=(const WordCounter &rhs);

    /**]
     * Checks if the word exists in the table. If the word does, the word
     * count for that given word increases, else, the word is added to the
     * table and the unique word count updates
     * @param word to search for
     * @return the word count
     */
    int addWord(std::string word);

    /**
     * Removes the word completely from the hash table. If the entry is part
     * of a linked list, the node is removed. The unique and total word
     * counts are updated
     * @param word to be removed
     */
    void remove(std::string word);

    /**
     * Returns the count of the specified work. If the words hasn't been
     * encounterd, 0 is returned.
     * @param word to return the count for
     * @return the count for a given word. If it doesn't exist, return 0
     */
    int getWordCount(std::string word);

    /**
     * Returns the current load factor of the hash table
     * @return the double for the load factor
     */
    double getLoadFactor();

    /**
     * Returns the total number of unique words identified in the hash table.
     * With ignore removed words.
     * @return count of unique words
     */
    int getUniqueWordCount();

    /**
     * Returns the total number of words encountered in the hashtables,
     * including duplicates.
     * @return the total word count
     */
    int getTotalWordCount();

    /**
     * Checks if the hash table is empty
     * @return true if empty, else false
     */
    bool empty();

private:
    int capacity; // variable to hold the capacity
    LinkedList **hTable; // hash table to hold the words and their respective
    // counts
    int hashFunction(std::string word);
};


#endif //P5_HASHING_WORDCOUNTER_H
