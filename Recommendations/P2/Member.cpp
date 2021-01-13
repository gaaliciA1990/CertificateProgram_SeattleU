//
// Created by garci on 9/17/2020.
//

#include "Member.h"

#include <utility>

using namespace std;

Member::Member() {
    count = 0;
    capacity = CAPACITY;
    memberArray = new memberInfo[capacity];
}

Member::Member(const Member &other) {
    count = 0;
    capacity = CAPACITY;
    memberArray = new memberInfo[capacity];

    for (int i = 0; i < size(); i++) {
        memberArray[i] = other.memberArray[i];
    }
}

Member &Member::operator=(const Member &rhs) {
    if (this == &rhs) {
        return *this;
    }
    for (int i = 0; i < size(); i++) {
        memberArray[i] = rhs.memberArray[i];
    }
    return *this;
}

Member::~Member() {
    clear();
}

int Member::addMember(std::string &name) {
    // create a member object to store the member details
    memberInfo *member = new memberInfo;
    int acctID, index = count;
    bool status;

    if (count >= capacity) {
        resize();
    }
    // create the account id for the new member
    acctID = count + 1;
    status = false;

    member->accountID = acctID;
    member->memberName = name;
    member->loginStatus = status;

    // add the contents of member to the member array
    memberArray[index] = *member;
    count++;

    // return the memberID, per the index, which will be count - 1
    return acctID;
}

std::string Member::findName(int memID) {
    int index = memID - 1;
    return memberArray[index].memberName;
}

bool Member::login(int memID) {
    if ((memID - 1) >= 0 && (memID - 1) < size()) {
        memberArray[memID - 1].loginStatus = true;
        return memberArray[memID - 1].loginStatus;
    } else {
        cout << "Invalid member account!" << endl;
        return false;
    }

}

void Member::logout(std::string name) {
    for (int i = 0; i < size(); i++) {
        if (memberArray[i].memberName == name) {
            memberArray[i].loginStatus = false;
            cout << memberArray[i].memberName << " is now logged out." << endl;
        }
    }
}

void Member::printAccount(int memID) {
    cout << memberArray[memID].accountID << ", ";
    cout << memberArray[memID].memberName << ", ";
    cout << memberArray[memID].loginStatus << endl;
}

void Member::printAllMembers() {
    for (int i = 0; i < size(); i++) {
        printAccount(i);
    }
}

int Member::size() {
    return count;
}

void Member::resize() {
    capacity *= 2; // increase the capacity

    memberInfo *tempArray = new memberInfo[capacity];

    for (int i = 0; i < size(); i++) {
        tempArray[i] = memberArray[i];
    }
    clear(); // delete the old array
    memberArray = tempArray;
}

void Member::clear() {
    for (int i = 0; i < size(); i++) {
        delete &memberArray[i];
    }
    delete memberArray;
}
