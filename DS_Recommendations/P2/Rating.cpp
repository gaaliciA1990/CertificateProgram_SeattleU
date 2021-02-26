//
// Created by garci on 9/17/2020.
//

#include "Rating.h"

Rating::Rating(int initialBookCapacity) {
    memCapacity = CAPACITY;
    bookCapacity = initialBookCapacity;
    // initialize new rating array with the size of the member and book capacity
    ratingArray = new int *[memCapacity];
    for (int i = 0; i < memCapacity; i++) {
        ratingArray[i] = new int[bookCapacity];
        for (int j = 0; j < bookCapacity; j++) {
            ratingArray[i][j] = RATE_START; // initialize ratings to 0
        }
    }
}

/*
Rating::Rating(const Rating &other) {

}

Rating &Rating::operator=(const Rating &rhs) {

}
 */

Rating::~Rating() {
    clear();
}

void Rating::addRating(int accountID, int bookID, int rating) {
    ratingArray[accountID - 1][bookID] = rating;
}

int Rating::getRatings(int accountID, int bookID) {
    return ratingArray[accountID - 1][bookID];
}

int Rating::mostSimilar(int accountID) {
    int similarityScore;
    int matchingMember;
    int highestScore = -10000;  // setting highestScore to a very small
    // number to ensure the max score is always
    // the highest

    for (int row = 0; row < memCapacity; row++) {
        for (int col = 0; col < bookCapacity; col++) {
            similarityScore += ratingArray[accountID][col] *
                               ratingArray[row][col];
        }
        if (similarityScore > highestScore) {
            highestScore = similarityScore;
            matchingMember = row + 1; // member id is equal to
        }
    }
    return matchingMember;
}

void Rating::addMember(int memID) {
    if (memberCount > memCapacity) {
        resizeRow();
    }
    for (int col = 0; col < bookCapacity; col++) {
        ratingArray[memID][col] = RATE_START;
    }
    memberCount++;
}

void Rating::addBook(int bookID) {
    if (bookCount > bookCapacity) {
        resizeCol();
    }
    for (int row = 0; row < memCapacity; row++) {
        ratingArray[row][bookID] = RATE_START;
    }
    bookCount++;
}

void Rating::resizeCol() {
    bookCapacity *= 2;
    int **tempArray = new int *[memCapacity];

    for (int row = 0; row < memCapacity; row++) {
        tempArray[row] = new int[bookCapacity];
        for (int col = 0; col < bookCapacity; col++) {
            tempArray[row][col] = ratingArray[row][col];
        }
    }

    clear();
    ratingArray = tempArray;
}

void Rating::resizeRow() {
    memCapacity *= 2;
    int **tempArray = new int *[memCapacity];

    for (int row = 0; row < memCapacity; row++) {
        tempArray[row] = new int[bookCapacity];
        for (int col = 0; col < bookCapacity; col++) {
            tempArray[row][col] = ratingArray[row][col];
        }
    }
    clear(); // delete the old array
    ratingArray = tempArray;
}

void Rating::clear() {
    for (int row = 0; row < memCapacity; row++) {
        delete[] ratingArray[row];
    }
    delete[] ratingArray;
}
