//
// Created by garci on 11/2/2020.
// Version 1.0
//

#include "PatientPriorityQueue.h"

PatientPriorityQueue::PatientPriorityQueue() {
    // maintained as empty to create the zero arg constructor
}

PatientPriorityQueue::PatientPriorityQueue(const Patient *patientData, int
arrDataCount) {
    for (int i = 0; i < arrDataCount; i++) {
        patients.push_back(patientData[i]);
    }
    heapify();
}

PatientPriorityQueue::PatientPriorityQueue(const PatientPriorityQueue &other) {
    std::vector<Patient> copy = other.copy();

    for (int i = 0; i < other.size(); i++) {
        patients.push_back(copy[i]);
    }
    heapify();
}

void PatientPriorityQueue::enqueue(Patient *newPatient) {
    patients.push_back(*newPatient);
    percolateUp(patients.size() - 1);
}

Patient PatientPriorityQueue::dequeue() {
    const int ROOT = 0;
    Patient value = peek();

    patients[0] = patients[patients.size() - 1];
    patients.pop_back();
    percolateDown(ROOT);
    return value;
}

bool PatientPriorityQueue::empty() const {
    return patients.size() == 0;
}

Patient PatientPriorityQueue::peek() const {
    if (empty()) {
        throw std::invalid_argument("Empty queue found!");
    }
    return patients[0];
}

void PatientPriorityQueue::heapsort(Patient *patientData, int arrDataCount) {
    PatientPriorityQueue heapQ(patientData, arrDataCount);

    for (int i = arrDataCount - 1; i >= 0; i--) {
        patientData[i] = heapQ.dequeue();
    }
}

//VERIFY THIS IS WORKING HOW YOU WANT
bool PatientPriorityQueue::isValid() {
    for (int i = patients.size() - 1; i > 0; i--) {
        if (patients[parent(i)].compareTo(patients[i]) == -1) {
            return false;
        }
    }
    return true;
}

void PatientPriorityQueue::percolateUp(int index) {
    if (index > 0) {
        int p = parent(index);
        // if in violation of invariants, swap it up
        if (patients[p].compareTo(patients[index]) == 1) {
            std::swap(patients[p], patients[index]);
            percolateUp(p);
        }
    }
}

void PatientPriorityQueue::percolateDown(int index) {
    if (hasLeft(index)) {
        // get the max of one or two children
        int child = left(index);
        if (hasRight(index)) {
            int r = right(index);
            if (patients[r].compareTo(patients[child]) == -1) {
                child = r;
            }
        }
        // if in violation of invariants, swap it down
        if (patients[child].compareTo(patients[index]) == -1) {
            std::swap(patients[index], patients[child]);
            percolateDown(child);
        }
    }
}

void PatientPriorityQueue::heapify() {
    for (int index = patients.size() / 2; index >= 0; index--) {
        percolateDown(index);
    }
}

int PatientPriorityQueue::parent(int childIndex) {
    return (childIndex - 1) / 2;
}

int PatientPriorityQueue::left(int parentIndex) {
    return parentIndex * 2 + 1;
}

int PatientPriorityQueue::right(int parentIndex) {
    return left(parentIndex) + 1;
}

bool PatientPriorityQueue::hasLeft(int parentIndex) const {
    return left(parentIndex) < patients.size();
}

bool PatientPriorityQueue::hasRight(int parentIndex) const {
    return right(parentIndex) < patients.size();
}

int PatientPriorityQueue::size() const {
    return patients.size();
}

std::vector<Patient> PatientPriorityQueue::copy() const {
    std::vector<Patient> copyPatients;

    for (int i = 0; i < size(); i++) {
        copyPatients.push_back(patients[i]);
    }
    return copyPatients;
}
