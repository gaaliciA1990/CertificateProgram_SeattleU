//
// Created by garci on 11/15/2020.
//

#include "WordCounter.h"

WordCounter::WordCounter(int cap) {
    this->capacity = cap;
    // Create an array
    hTable = new LinkedList *[capacity];
    // fill the array with linked lists
    for (int i = 0; i < capacity; i++) {
        hTable[i] = new LinkedList();
    }
}

WordCounter::~WordCounter() {
    for (int i = 0; i <= capacity; i++) {
        LinkedList *head = hTable[i];
        delete head;
    }
}

WordCounter::WordCounter(const WordCounter &other) {
    this->capacity = other.capacity;
    hTable = new LinkedList *[capacity];

    for (int i = 0; i < capacity; i++) {
        hTable[i] = new LinkedList(*other.hTable[i]);
    }
}


WordCounter &WordCounter::operator=(const WordCounter &rhs) {
    if (this == &rhs) {
        return *this;
    }
    for (int i = 0; i < capacity; i++) {
        hTable[i] = rhs.hTable[i];
    }
    return *this;
}


int WordCounter::addWord(std::string word) {
    int index = hashFunction(word);
    LinkedList *location = hTable[index];
    if (!location->search(word)) {
        location->add(word, 1);
        return 1;  // new words will always return 1
    } else {
        return location->incrementCount(word);
    }
}

void WordCounter::remove(std::string word) {
    int index = hashFunction(word);
    LinkedList *location = hTable[index];
    location->remove(word);
}

int WordCounter::getWordCount(std::string word) {
    int index = hashFunction(word);
    LinkedList *wordCount = hTable[index];
    if (wordCount->search(word)) {
        return wordCount->getWordCount(word);
    } else {
        return 0;  // No word found
    }
}

double WordCounter::getLoadFactor() {
    return (double) getUniqueWordCount() / (double) capacity;
}

int WordCounter::getUniqueWordCount() {
    int uniqueWordCount = 0;
    for (int i = 0; i < capacity; i++) {
        LinkedList *head = hTable[i];
        uniqueWordCount += head->distinctWordCount();
    }
    return uniqueWordCount;
}

int WordCounter::getTotalWordCount() {
    int totalWordCount = 0;
    for (int i = 0; i < capacity; i++) {
        LinkedList *head = hTable[i];
        totalWordCount += head->totalWordCount();
    }
    return totalWordCount;
}

bool WordCounter::empty() {
    for (int i = 0; i < capacity; i++) {
        LinkedList *head = hTable[i];
        if (!head->emtpy()) {
            return false;
        }
    }
    return true;
}

int WordCounter::hashFunction(std::string word) {
    std::hash<std::string> h;
    int index = h(word) % capacity;
    return index;
}