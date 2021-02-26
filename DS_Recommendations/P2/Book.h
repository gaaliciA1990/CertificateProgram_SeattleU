//
// Created by garci on 9/17/2020.
//

#ifndef P2_BOOK_H
#define P2_BOOK_H
#include <iostream>

/**
 * This class will create a book object and add elements to the object for
 * storing and extracting data on books from a file. Given the nature of the
 * lab, a copy ctor and assignment operator were not implemented for this as
 * they are not called.
 */
class Book {
public:
    /**
     * Default constructor for the book object.
     */
    Book();

    /**
    * Copy constructor
    * @param other  Book to copy
    */
    Book(const Book &other);

    /**
     * Assignment operator
     * @param rhs Book to copy
     * @return Book
     */
    Book &operator=(const Book &rhs);

    /**
     * Destructor for the book object
     */
    ~Book();

    /**
     * This will add a book and it's details to the file
     * @param title of the book
     * @param author of the book
     * @param year the book was published
     * @return bookID, which maps to a single book info/object.
     */
    int addBook(std::string &author, std::string &title, std::string &year);

    /**
     * Searches for a book based on the ISBN
     * @param isbn The randomly generated isbn number
     * @return the bookID (location)
     */
    int findBook(std::string isbn);
    /**
     * Print the details of a single book
     * @param bookID
     */
    void printBook(int bookID) const;

    /**
     * How many books have been added?
     * @return the number of books in the list
     */
    int size() const;

private:
    static const int CAPACITY = 100;
    struct bookInfo {
        std::string isbn;   // book identified
        std::string author; // author of the book, first and last name
        std::string title;  // string holding the title
        std::string year;   // year the book was published
    };
    bookInfo *bookArray;  // create an array of books with their information
    int count;  // track the books added
    int capacity;   // variable to hold the const value

    /**
     * Automatically enlarge if we get more than INITIAL_CAPACITY books in
     * the list.
     */
    void resize();

    /**
     * This will delete all of the indices within the array and delete the array
     */
    void clear();
};

#endif //P2_BOOK_H