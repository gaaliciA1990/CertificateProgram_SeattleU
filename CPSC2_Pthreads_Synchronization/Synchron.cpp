#include <iostream>
#include <pthread.h>
#include <vector>
#include <cstring>
#include <exception>
#include <sstream>
#include <thread>

/**
 * Author: Alicia Garcia
 * Version: 1.0
 * Date: 5/27/2021 18:26
 * Class: Seattle University
 * This is free and unencumbered software released into the public domain
 */

int allowedID;
pthread_mutex_t lock;

using namespace std;

/**
 * This class will print which thread's turn it is and isn't, and then after
 * 2 times where the thread has hit their turn, this will print completed. To
 * avoid printing the entire log, the thread will only print "Not thread X's
 * turn' after it's hit it's turn.
 * @param arg The threadID number assigned in the main method
 * @return a void pointer
 */
void *allowedCheck(void *arg) {
    int tID = *((int *) arg);
    int counter = 0;

    while (counter != 2) {
        pthread_mutex_lock(&lock);

        if (tID == allowedID) {
            printf("Thread %d's turn!\n", tID);
            if (allowedID < 3) {
                allowedID++;
                counter++;
            } else {
                allowedID = 1;
                counter++;
            }
        } else {
            printf("Not thread %d's Turn\n", tID);
        }
        pthread_mutex_unlock(&lock);
        this_thread::sleep_for (chrono::milliseconds (100));
        if (counter == 2) {
            printf("Thread %d completed!\n", tID);
        }
    }
}

/**
 * Main method for creating the thread and running them in sync. We also
 * initialize the mutex variable and validate all create actions are successful
 * @return 0 when success, else other numbers.
 */
int main() {
    vector<int> threadID;
    vector<pthread_t> threads;
    int threadMax = 3;
    allowedID = 1;

    if (pthread_mutex_init(&lock, NULL) != 0) {
        cout << "Mutex initiation failed!" << endl;
        return 1;
    }

    for (int a = 1; a <= threadMax; a++) {
        threadID.push_back(a);
    }

    for (int i = 0; i < threadMax; i++) {
        pthread_t thr;
        int error = pthread_create(&thr, NULL, allowedCheck, &threadID.at(i));
        if (error) {
            cout << "Thread creation failed for stat2: " << strerror(error)
                 << endl;
            return 1;
        }
        threads.push_back(thr);
    }

    for (unsigned int thread : threads) {
        pthread_join(thread, NULL);
    }
}