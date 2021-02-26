//
// Created by garci on 10/7/2020.
//


#ifndef P2_MAIN_H
#define P2_MAIN_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <bits/stdc++.h>
#include "Rating.h"
#include "Book.h"
#include "Member.h"

/**
 * This method will read the bookFile and store the information in a book object.
 * The book object is then added to our bookArray.
 * @param bookFile The user inputted bookFile to read from
 * @return the book array when a bookFile is present, else nullptr.
 */
Book *readBookFile(std::string bookFile);

/**
 * This will call the print book method and print all book items in our
 * bookArray
 * @param book The book object holding all of our bookInfo
 */
void printBooks(Book *book);

/**
 * This method will read the ratings ratingsFile and populate the member and rating
 * arrays with the contents of the ratingsFile.
 * @param members The member array to populate with the names
 * @param ratings The ratings 2D array to populate with the ratins for each
 *                book and member
 * @param ratingsFile The ratingsFile to be read from
 */
void readRatingsFile(Member *members, Rating *ratings, std::string ratingsFile);

/**
 * This will print all of the ratings for each book for a given member and
 * @param ratings
 * @param members
 * @param books
 * @param memberID
 */
void viewRatings(Rating *ratings, Member *members, Book *books, int memberID);

void menuOptions(Member *members, Book *books, Rating *ratings);


#endif //P2_MAIN_H
