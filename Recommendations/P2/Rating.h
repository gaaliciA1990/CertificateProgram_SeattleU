//
// Created by garci on 9/17/2020.
//

#ifndef P2_RATING_H
#define P2_RATING_H

#include <iostream>
#include "Book.h"
#include "Member.h"

class Rating {
public:
    /**
     * Constructor
     * @param initialBookCapacity The starting number of books to have ratings
     */
    Rating(int initialBookCapacity);

    /**
     * Copy constructor
     * @param other The rating to copy
     */
    Rating(const Rating &other);

    /**
     * Assignment operator to create a deep copy
     * @param rhs   The object on the right hand side (rhs)
     * @return Rating
     */
    Rating &operator=(const Rating &rhs);

    /**
     * Destructor
     */
    ~Rating();

    /**
     * Add a new rating for a given user and book.
     * @param accountID The member to associate the rating to
     * @param bookID The book to associate the rating with
     * @param rating The rating for the given book
     */
    void addRating(int accountID, int bookID, int rating);


    /**
     * This method will show the rating for a single book for a given member
     * @param accountID The member associated with the rating
     * @param bookID  The book associated with the rating
     * @return the rating for the book and member provided
     */
    int getRatings(int accountID, int bookID);

    /**
     * This will compare the ratings for a given member to the ratings for
     * all members in our program and return book suggestions
     * @param accountID The member to be compared against the collective members
     * @return the suggestions for most similar ratings
     */
    int mostSimilar(int accountID);

    /**
     * This will add new members row to our rating array
     * @param memID
     */
    void addMember(int memID);

    /**
     * This will add new books column to our rating array
     * @param bookID
     */
    void addBook(int bookID);

private:
    const static int CAPACITY = 100;
    const static int RATE_START = 0;
    int **ratingArray;
    int memCapacity;
    int bookCapacity;
    int memberCount = 0;
    int bookCount = 0;

    /**
     * Resize the column (book capacity) as new books are added
     */
    void resizeCol();

    /**
     * Resize the row (member capacity) as new members are added
     */
    void resizeRow();

    /**
     * This will delete all of the indices within the array and delete the array
     */
    void clear();
};

#endif //P2_RATING_H