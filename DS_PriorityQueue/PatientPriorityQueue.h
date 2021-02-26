//
// Created by garci on 11/2/2020.
// Version 1.0
//

#ifndef P4_HIGHESTPRIORITY_PATIENTPRIORITYQUEUE_H
#define P4_HIGHESTPRIORITY_PATIENTPRIORITYQUEUE_H

#include <iostream>
#include <string>
#include <vector>
#include "Patient.h"

class PatientPriorityQueue {
public:
    /**
     * Zero-arg constructor.
     */
    PatientPriorityQueue();

    /**
     * All-at-once constructor.
     * @param data  array of integers to enqueue
     * @param size  number of integers in patients
     */
    PatientPriorityQueue(const Patient *patientData, int arrDataCount);

    /**
     * Copy constructor to create a new copy of the Priority queue
     * @param other Queue to be copied
     */
    PatientPriorityQueue(const PatientPriorityQueue &other);

    /**
     * Add an element to the queue. Items don't need to be unique.
     * @param newPatient to add to the priority queue
     */
    void enqueue(Patient *newPatient);

    /**
     * Remove the least element from the queue.
     * @return the least element
     */
    Patient dequeue();

    /**
     * Check if there are elements in the queue.
     * @return true if there are no elements, else false
     */
    bool empty() const;

    /**
     * Fetch the element that would be returned by the dequeue.
     * @return the least element
     */
    Patient peek() const;

    /**
     * Sort the given array in place in ascending order using heapsort,
     * O(n log n).
     * @param patientData to be sorted
     */
    static void heapsort(Patient *patientData, int arrDataCount);

    /**
     * Check if the heap invariants are true for every node.
     * @return true if every node is correct
     */
    bool isValid();

    /**
     * Return the size of the queue
     * @return size value
     */
    int size() const;

private:
    std::vector<Patient> patients;

    /**
     * The value at patients[index] may violate the heap invariants by being too
     * high.
     * If so, fix it by swapping with ancestors as necessary.
     *
     * @param index of patients that may be too low relative to parent (and further
     *              ancestors)
     */
    void percolateUp(int index);

    /**
     * The value at patients[index] may violate the heap invariants by being too
     * low. If so, fix it by swapping with descendants as necessary.
     *
     * @param index of patients that may be too high relative to children (and
     *              further descendants)
     */
    void percolateDown(int index);

    /**
     * Construct a heap from arbitrarily-ordered elements in the patients array.
     */
    void heapify();

    /**
     * Get the index of the parent of a given node in this heap.
     * Does not check if parent index is the root (parent(0) returns 0).
     *
     * @param childIndex child address
     * @return index of the left child of parentIndex in the patients array
     */
    static int parent(int childIndex);

    /**
     * Get the index of the left child of a given node in this heap.
     * Does not check if the child is a current member of this heap.
     *
     * @param parentIndex parent address
     * @return index of the left child of parentIndex in the patients array
     */
    static int left(int parentIndex);

    /**
     * Get the index of the right child of a given node in this heap.
     * Does not check if the child is a current member of this heap.
     *
     * @param parentIndex parent address
     * @return index of the right child of parentIndex in the patients array
     */
    static int right(int parentIndex);

    /**
     * Check if the given node has a left child.
     *
     * @param parentIndex parent address
     * @return true if the left child of parentIndex is a current member of the
     *         heap
     */
    bool hasLeft(int parentIndex) const;

    /**
     * Check if the given node has a right child.
     *
     * @param parentIndex parent address
     * @return true if the right child of parentIndex is a current member of
     *         the heap
     */
    bool hasRight(int parentIndex) const;

    /**
     * Helper method to copy the queue
     * @return a new priority queue
     */
    std::vector<Patient> copy() const;
};


#endif //P4_HIGHESTPRIORITY_PATIENTPRIORITYQUEUE_H
