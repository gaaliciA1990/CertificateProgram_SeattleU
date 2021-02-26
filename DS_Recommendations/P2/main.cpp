
#include "main.h"

using namespace std;

void readRatingsFile(Member **pMember, Rating ***pRating, string basicString);

/**
 *
 * @return
 */
int main() {
    string bookFile;
    string ratingsFile;
    Book *books;

    cout << "Enter the books file name or path: ";
    cin >> bookFile;
    cout << endl;   //add new line after path input

    cout << "Enter ratings file name or path:  ";
    cin >> ratingsFile;

    books = readBookFile(bookFile);
    // If the books file was not able to be created successfully, close the
    // program
    if (books == nullptr) {
        cout << "Unable to populate books file, please try again." << endl;
        return EXIT_FAILURE;
    }

    Member *members = new Member();
    Rating *ratings = new Rating(books->size());

    readRatingsFile(members, ratings, ratingsFile);

    // Print the number of book and full member list
    cout << "\n# of books: " << books->size() << endl;
    cout << "# of members: " << members->size() << endl << endl;

    menuOptions(members, books, ratings);

    delete books;
    delete members;
    delete ratings;
    return EXIT_SUCCESS;
}


Book *readBookFile(string bookFile) {
    ifstream inFile;    // Instantiating the read bookFile funtionality
    string bookDetails;
    string author, title, year; // variables to hold the data from bookDetails

    int count = 0;  // counter variable


    Book *bookData = new Book();
    inFile.open(bookFile);  // Opens the bookFile

    if (inFile) {
        while (getline(inFile, bookDetails, '\n')) {
            string str; // temp variable to hold the first line of text
            stringstream ss(bookDetails); // string stream will read bookDetails

            while (getline(ss, str, ',')) {
                if (count == 0) {
                    author = str;
                } else if (count == 1) {
                    title = str;
                } else if (count == 2) {
                    year = str;
                }
                count++;
                if (count >= 3) {
                    count = 0; // reset count
                    // add the book object to the array of books
                    bookData->addBook( author, title, year);
                }
            }
        }
    } else {
        cout << "ERROR: cannot open bookFile or bookFile doesn't exist.\n";
        return nullptr; // return null if no bookFile is found
    }
    return bookData;
}

void printBooks(Book *book) {
    // print the book information stored.
    for (int i = 0; i < book->size(); i++) {
        book->printBook(i);
        cout << endl;
    }
}

void readRatingsFile(Member *members, Rating *ratings, string ratingsFile) {
    ifstream inFile;
    inFile.open(ratingsFile);  // Opens the ratingsFile

    // if the ratingsFile exists, read the ratingsFile and write to our arrays
    if (inFile) {
        int index = 0;  // the index to cycle thru the ratingsFile
        string number, row; // variable holding the rating number and point to row
        int rate;   // variable hold the int rating number after conversion
        int memberID;

        while (getline(inFile, row))
            // reads the name and stores in the member array
            if (index % 2 == 0) {
                memberID = members->addMember(row);
                index++;
            }
                //reads the ratings and converts to int and stores in ratings array
            else if (index % 2 != 0) {
                int col = 0;
                for (int i = 0; i < row.size(); i++) {
                    // the character in the row of the ratingsFile
                    char x = row[i];
                    if (x == ' ') {
                        // stringstream object to convert string to int
                        stringstream r(number);

                        // object streams the string value to the int variable
                        r >> rate;
                        ratings->addRating(memberID, col, rate);
                        number = "";  // reset our string variable to empty
                        col++;
                    } else {
                        number += x; //append the char to our string variable
                    }
                }
                index++;
            }
    } else {
        cout << "ERROR: cannot open ratingsFile.\n";
    }
    inFile.close();
}

void viewRatings(Rating *ratings, Member *members, Book *books, int memberID) {
    int rating;

    cout << members->findName(memberID) << "'s ratings..." << endl;

    for (int col = 0; col < books->size(); col++) {
        rating = ratings->getRatings(memberID, col);
        books->printBook(col);
        cout << " => rating: " << rating << endl;
    }
    cout << endl;
}
void viewTopRatings(Rating *ratings, Member *members, Book *books, int
memberID, int topRating) {
    int rating;

    for (int col = 0; col < books->size(); col++) {
        rating = ratings->getRatings(memberID, col);
        if (rating == topRating) {
            books->printBook(col);
            cout << endl;
        }
    }
}
void menuOptions(Member *members, Book *books, Rating *ratings) {
    int options;
    bool loginStatus;
    int loggedInUser;
    string placeholder; // to clear the new line after reading an int


    while (true) {

        cout << "************** MENU **************" << endl;
        cout << "* 1. Add a new member            *" << endl;
        cout << "* 2. Add a new book              *" << endl;
        if (!loginStatus) {
            cout << "* 3. Login                       *" << endl;
            cout << "* 4. Quit                        *" << endl;
        }
        else {
            cout << "* 3. Rate book                   *" << endl;
            cout << "* 4. View ratings                *" << endl;
            cout << "* 5. See recommendations         *" << endl;
            cout << "* 6. Logout                      *" << endl;
        }
        cout << "**********************************" << endl;

        cout << "\nEnter a menu option: ";
        cin >> options;
        getline(cin, placeholder);
        cout << endl;

        string name, author, title, year, isbn;
        int acctID, bookID, rating;

        switch (options) {
            case 1:
                cout << "Enter the name of the new member: ";
                getline(cin, name);

                acctID = members->addMember(name);
                ratings->addMember(acctID);

                cout << name << " (account #: " << acctID << ") was added."
                     << endl;
                break;
            case 2:
                cout << "Enter the author of the new book: ";
                getline(cin, author);

                cout << "Enter the title of the new book: ";
                getline(cin, title);

                cout << "Enter the year (or range of years) of the new book: ";
                getline(cin, year);

                bookID = books->addBook(author, title, year);
                ratings->addBook(bookID);
                books->printBook(bookID);
                cout << " was added! " << endl << endl;
                break;
            case 3:
                if (!loginStatus) {
                    cout << "Enter member account: ";
                    cin >> acctID;
                    getline(cin, placeholder);

                    loginStatus = members->login(acctID);
                    if (loginStatus) {
                        loggedInUser = acctID;
                        cout << "\n" << members->findName(acctID);
                        cout << ", you're logged in! Welcome back!" << endl;
                    }
                }
                else {
                    cout << "Enter the ISBN for the book you'd like to rate: ";
                    getline(cin, isbn);
                    bookID = books->findBook(isbn);

                    cout << "Enter your rating: ";
                    cin >> rating;
                    if (rating != 5 && rating != 3 && rating != 1 && rating
                    != 0 && rating != -3 && rating != -5) {
                        cout << "Invalid rating, please use 5, 3, 1, 0, -3, "
                                "-5." << endl;
                        break;
                    }
                    getline(cin, placeholder);
                    ratings->addRating(loggedInUser, bookID, rating);

                    cout << "Your new rating for ";
                    books->printBook(bookID);
                    cout << " => rating: " << ratings->getRatings(loggedInUser,
                                                                  bookID) <<
                                                                  endl;
                }
                break;
            case 4:
                if (!loginStatus) {
                    cout << "Thank you for using the Book Recommendation "
                            "Program!" << endl << endl;
                    return;
                } else {
                    viewRatings(ratings, members, books, loggedInUser);
                }
                break;
            case 5:
                acctID = ratings->mostSimilar(loggedInUser);

                cout << "You have similar taste in books as " <<
                members->findName(acctID) << "!" << endl << endl;
                cout << "Here are the books they really liked:" << endl;
                viewTopRatings(ratings, members, books, acctID, 5);

                cout << "\nAnd here are the books they liked:" << endl;
                viewTopRatings(ratings, members, books, acctID, 3);
                cout << endl;
                break;
            case 6:
                if (!loginStatus) {
                    cout << "Invalid input, please try again." << endl;
                } else {
                    name = members->findName(loggedInUser);
                    members->logout(name);
                    loginStatus = false;
                    loggedInUser = -1;
                }
                break;
            default:
                cout << "Invalid input, please try again." << endl;
                break;
        }
    }
}
