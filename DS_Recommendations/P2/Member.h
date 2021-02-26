//
// Created by garci on 9/17/2020.
//

#ifndef P2_MEMBER_H
#define P2_MEMBER_H

#include <iostream>
#include "Rating.h"
#include "Book.h"

class Member {
public:
    /**
     * Constructor for the member object that is set to XX.
     */
    Member();

    /**
     * Copy constructor
     * @param other The other member to copy
     */
    Member(const Member &other);

    /**
     * Assignment operator to make a deep copy
     * @param rhs   The object on the right hand side (rhs)
     * @return Member
     */
    Member &operator=(const Member &rhs);

    /**
     * Destructor
     */
    ~Member();

    /**
     * Adds a new member to the member file and generates an new accountID id
     * for them
     * @param name  of the members in the list
     * @return member id
     */
    int addMember(std::string &name);

    /**
     * Find the name of a given member
     * @param memID as returned in the addMember method
     * @return the name of the member
     */
    std::string findName(int memID);

    /**
     * Logs into the account
     * @param memID The users accountID
     * @return true if the member logged in successfully, else false
     */
    bool login(int memID);

    /**
     * This will end the session for the the user when they ask to log out
     * @param name The member to logout of the program
     */
    void logout(std::string name);

    /**
     * Print the information about a given member
     * @param memID The users accountID
     */
    void printAccount(int memID);

    /**
     * Print the full member list details
     */
    void printAllMembers();

    /**
     * Get the cardinality of the list
     * @return the number of successful adds to the member list
     */
    int size();

private:
    static const int CAPACITY = 100;
    struct memberInfo {
        int accountID;
        std::string memberName;
        bool loginStatus;
    };
    memberInfo *memberArray;
    int count;
    int capacity;

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

#endif //P2_MEMBER_H