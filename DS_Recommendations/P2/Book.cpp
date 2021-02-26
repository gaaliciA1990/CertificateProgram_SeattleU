//
// Created by garci on 9/17/2020.
//

#include <iostream>
#include <bits/stdc++.h>
#include "Book.h"

using namespace std;

Book::Book() {
    count = 0;
    capacity = CAPACITY;
    bookArray = new bookInfo[capacity];
    srand(time(NULL));  // initialize random seed
}

Book::Book(const Book &other) {
    count = 0;
    capacity = CAPACITY;
    bookArray = new bookInfo[capacity];

    for (int i = 0; i < size(); i++) {
        bookArray[i] = other.bookArray[i];
    }
}

Book &Book::operator=(const Book &rhs) {
    if (this == &rhs) {
        return *this;
    }
    for (int i = 0; i < size(); i++) {
        bookArray[i] = rhs.bookArray[i];
    }
    return *this;
}

Book::~Book() {
    clear();
}

int Book::addBook(string &author, string &title, string &year) {
    // Create book object to store the book information
    bookInfo *book = new bookInfo();
    int index = count;
    int random; // will be used as a place holder for my ISBN


    if (count >= capacity) {
        resize();
    }
    //generate a random num starting at 10000
    random = rand() % 1000 + 10000;
    // to avoid potential duplicate random nums, add delay
    this_thread::sleep_for(chrono::microseconds(2));

    string isbn = to_string(random);  // convert the int to str

    book->isbn = isbn;
    book->author = author;
    book->title = title;
    book->year = year;

    // add the contents of the book (the information stored) to the book array
    bookArray[count] = *book;
    count++;

    // return the location of the book per the index, which is the previous
    // count value before count++
    return index;
}

int Book::findBook(std::string isbn) {
    for (int i = 0; i < size(); i++) {
        if (bookArray[i].isbn == isbn) {
            return i;
        }
    }
    return -1; // Indicates the book can't be found
}

void Book::printBook(int bookID) const {
    cout << bookArray[bookID].isbn << ", ";
    cout << bookArray[bookID].author << ", ";
    cout << bookArray[bookID].title << ", ";
    cout << bookArray[bookID].year;
}

int Book::size() const {
    return count;
}

void Book::resize() {
    capacity *= 2; // increase capacity

    // create new bookArray with updated capacity
    bookInfo *tempArray = new bookInfo[capacity];

    for (int i = 0; i < size(); i++) {
        tempArray[i] = bookArray[i];
    }

    clear(); //delete the old array
    bookArray = tempArray;  // reassign the old array to the new temp array
}

void Book::clear() {
    for (int i = 0; i < size(); i++) {
        delete &bookArray[i];
    }
    delete bookArray;
}


