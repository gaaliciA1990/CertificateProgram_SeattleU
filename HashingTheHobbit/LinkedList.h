/**
 * This is a Linked List class to store the words and their respective counts.
 * This program is used by the WordCounter program.
 * @author Alicia Garcia
 * Course CPSC 5910-01
 * 11/16/2020 (Fall Quarter 2020)
 */

#ifndef P5_HASHING_LINKEDLIST_H
#define P5_HASHING_LINKEDLIST_H

#include <stdexcept>
#include <string>

/**
 * This class will create a Linked List which will allow for easy storing of
 * the word information
 */
class LinkedList {
public:
    /**
     * Constructor
     */
    LinkedList();

    /**
     * Destructor
     */
    ~LinkedList();

    /**
     * Copy constructor
     * @param other LL to copy
     */
    LinkedList(const LinkedList &other);

    /**
     * Assignment operator
     * @param rhs right hand side to copy
     * @return a copied LL
     */
    LinkedList &operator=(const LinkedList &rhs);

    /**
     * Add a word to the LL
     * @param word being added and used as a key
     * @param count the total time that word is encountered
     */
    void add(std::string word, int count);

    /**
     * Removes a word from the LL
     * @param word to be reomoved
     */
    void remove(std::string word);

    /**
     * Checks if the LL is empty
     * @return true if empty, else false
     */
    bool emtpy();

    /**
     * Will increase the count of a single word
     * @param word to be searched for and corresponding count increased
     * @return the count
     */
    int incrementCount(std::string word);

    /**
     * Searches for a given word within the LL
     * @param word to search for
     * @return true if found, else false
     */
    bool search(std::string word) const;

    /**
     * This will return the word count corresponding to a given word
     * @param word to search for the count
     * @return the count for that word
     */
    int getWordCount(std::string word) const;

    /**
     * This will count the total distinct words in the linked list.
     * @return the count of unique words
     */
    int distinctWordCount();

    /**
     * This will sum the total counts for all distinct words in the linked list
     * @return the total number of words
     */
    int totalWordCount();

private:
    struct ListElem {
        std::string word;
        int count;
        ListElem *next;

        // convenience ctor
        ListElem(std::string wrd, int cnt, ListElem *n) {
            word = wrd;
            count = cnt;
            next = n;
        }
    };

    ListElem *head;

    /**
     * Helper method for deleting LL data
     */
    void clear();

    /**
     * helper method for copying LL
     * @param headToCopy the word to copy
     * @return a new ListElem
     */
    static ListElem *copy(ListElem *headToCopy);
};

#endif //P5_HASHING_LINKEDLIST_H
