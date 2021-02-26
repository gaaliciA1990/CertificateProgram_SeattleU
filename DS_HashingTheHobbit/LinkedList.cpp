//
// Created by garci on 11/16/2020.
//
#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList() {
    head = nullptr;
}

LinkedList::~LinkedList() {
    clear();
}

LinkedList::LinkedList(const LinkedList &other) {
    head = copy(other.head);
}

LinkedList &LinkedList::operator=(const LinkedList &rhs) {
    if (&rhs != this) {
        clear();
        head = copy(rhs.head);
    }
    return *this;
}

void LinkedList::clear() {
    while (head != nullptr) {
        ListElem *toDelete = head;
        head = head->next;
        delete toDelete;
    }
}

void LinkedList::add(string word, int count) {
    if (word == "")
        throw invalid_argument("Cannot have a payload of empty string (means "
                               "not found when returned from search)");
    head = new ListElem(word, count, head);
}

bool LinkedList::search(string word) const {
    for (ListElem *cur = head; cur != nullptr; cur = cur->next) {
        if (cur->word == word)
            return true;
    }
    return false; // not found
}

LinkedList::ListElem *LinkedList::copy(LinkedList::ListElem *headToCopy) {
    ListElem anchor("", 0, nullptr), *source, *tail;
    tail = &anchor;
    for (source = headToCopy; source != nullptr; source = source->next) {
        tail->next = new ListElem(source->word, source->count, nullptr);
        tail = tail->next;
    }
    return anchor.next;
}

void LinkedList::remove(string word) {
    if (head == nullptr)
        return;

    // special case if found at head of list
    if (head->word == word) {
        ListElem *toDelete = head;
        head = head->next;
        delete toDelete;
        return;
    }

    // normal case is to find later down the list
    ListElem *prior = head;
    for (ListElem *cur = head->next; cur != nullptr; cur = cur->next) {
        if (cur->word == word) {
            prior->next = cur->next;
            delete cur;
            return;
        }
        prior = prior->next;
    }
}

bool LinkedList::emtpy() {
    return head == nullptr;
}

int LinkedList::incrementCount(std::string word) {
    for (ListElem *cur = head; cur != nullptr; cur = cur->next) {
        if (cur->word == word) {
            cur->count++;
            return cur->count;
        }
    }
    return 0; // return 0 to indicate no match
}

int LinkedList::getWordCount(std::string word) const {
    for (ListElem *cur = head; cur != nullptr; cur = cur->next) {
        if (cur->word == word) {
            return cur->count;
        }
    }
    return 0; // return 0 to indicate no match
}

int LinkedList::distinctWordCount() {
    int count = 0;
    for (ListElem *cur = head; cur != nullptr; cur = cur->next) {
        count++;
    }
    return count;
}

int LinkedList::totalWordCount() {
    int count = 0;
    for (ListElem *cur = head; cur != nullptr; cur = cur->next) {
        count += cur->count;
    }
    return count;
}