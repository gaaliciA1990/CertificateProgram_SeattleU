//
// Created by garci on 9/23/2020.
//

#include "SandPileX.h"

using namespace std;

SandPileX::SandPileX() {
    abelian = new int[SIZE];
    setPile(ZERO);
}

SandPileX::SandPileX(const int *pile) {
    abelian = new int[SIZE];
    setPile(pile);
}

SandPileX::SandPileX(const SandPileX *copy) {
    abelian = new int[SIZE];
    setPile(copy->abelian);
}

SandPileX &SandPileX::operator=(const SandPileX &other) {
    if (this == &other) {
        return *this;
    }
    setPile(other.abelian);
    return *this;
}

SandPileX::~SandPileX() {
    delete abelian;
}

void SandPileX::setPile(const int *cell) {
    for (int i = 0; i < SIZE; i++) {
        if (i < 0) {
            cout << "Warning, negative number found in SandPileX!" << endl;
            return; //Do nothing if negative number found
        }
    }
    for (int i = 0; i < SIZE; i++) {
        abelian[i] = cell[i];
    }
}

int *SandPileX::addPile(const int *a, const int *b) {
    for (int i = 0; i < SIZE; i++) {
        abelian[i] = a[i] + b[i];
    }
    // be sure to stabilize the sum afterwards
    if (!isStable()) {
        stabilize();
    }
    return abelian;
}

bool SandPileX::isInGroup() {
    //Create a copy of the current object so we are not changing the existing
    // pile array
    SandPileX *copy = new SandPileX(this);

    *copy = this;  // copy the values of this sandpile to the copy variable

    //variable to hold the sum from copy, ensuring only the copy is passed
    // through
    int *sum = copy->addPile(copy->abelian, ZERO);

    for (int i = 0; i < SIZE; i++) {
        // compare the sum to the original abelian, not the copy
        if (sum[i] != abelian[i]) {
            return false;
        }
    }
    return true;
}

bool SandPileX::isStable() const {
    // iterate through the array to the end of the array (move the for loop
    // to main.cpp)
    for (int i = 0; i < SIZE; i++) {
        // check if the value at that point is greater than our MAX_STABLE.
        // Return False if greater than 3, else true
        if (abelian[i] > MAX_STABLE) {
            return false;
        }
    }
    return true;
}

int SandPileX::index(int row, int col) {
    return row * DIM + col;
}

void SandPileX::stabilize() {
    //Code optimized after solution shared
    while (!isStable()) {
        for (int i = 0; i < SIZE; i++) {
            if (abelian[i] > MAX_STABLE) {
                int row = i / DIM;
                int col = i % DIM;
                abelian[i] -= MAX_STABLE + 1; // subtract 4 to perform topple
                if (row > 0) {
                    abelian[index(row - 1, col)] += 1;
                }
                if (col > 0) {
                    abelian[index(row, col - 1)] += 1;
                }
                if (row + 1 < DIM) {
                    abelian[index(row + 1, col)] += 1;
                }
                if (col + 1 < DIM) {
                    abelian[index(row, col + 1)] += 1;
                }
            }
        }
    }
}

int SandPileX::recursiveTotalAbelians(int index) {
    int count = 0; //counter variable

    for (int i = 0; i <= MAX_STABLE; i++) {
        abelian[index] = i;
        // Set the stopping point for recursion
        if (index == SIZE - 1) {
            if (isInGroup()) {
                count++;
            }
        }
        else {
            count += recursiveTotalAbelians(index + 1);
        }
    }
    return count;
}

string SandPileX::toString() const {
    string strPile;
    for (int i = 0; i < SIZE; i++) {
        strPile.append(to_string(abelian[i]));
        strPile.append(" ");
        if ((i + 1) % DIM == 0 && i != 0 && i != (SIZE - 1)) {
            strPile.append("/ ");
        }
    }
    return strPile;
}