//
// Created by garci on 9/14/2020.
//

#include "SandPile.h"

using namespace std;

SandPile::SandPile() {
    abelian = new int[SIZE];
    setPile(ZERO);
}

SandPile::SandPile(const int *pile) {
    abelian = new int[SIZE];
    setPile(pile);
}

SandPile::SandPile(const SandPile *copy) {
    abelian = new int[SIZE];
    setPile(copy->abelian);
}

SandPile &SandPile::operator=(const SandPile &other) {
    if (this == &other) {
        return *this;
    }
    setPile(other.abelian);
    return *this;
}

SandPile::~SandPile() {
    delete abelian;
}

void SandPile::setPile(const int *cell) {
    for (int i = 0; i < SIZE; i++) {
        if (i < 0) {
            cout << "Warning, negative number found in SandPile!" << endl;
            return; //Do nothing if negative number found
        }
    }
    for (int i = 0; i < SIZE; i++) {
        abelian[i] = cell[i];
    }
}

int *SandPile::addPile(const int *a, const int *b) {
    for (int i = 0; i < SIZE; i++) {
        abelian[i] = a[i] + b[i];
    }
    // be sure to stabilize the sum afterwards
    if (!isStable()) {
        stabilize();
    }
    return abelian;
}

bool SandPile::isInGroup() {
    //Create a copy of the current object so we are not changing the existing
    // pile array
    SandPile *copy = new SandPile();

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

bool SandPile::isStable() const {
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

int SandPile::index(int row, int col) {
    return row * DIM + col;
}

void SandPile::stabilize() {
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

int SandPile::totalAbelianGroups() {
    int startPile[] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //initial starting array
    setPile(startPile); //set our Abelian pile to the startPile
    int count = 0; //counter variable

    //the nine level nested for loop will generate all permutations of the
    // 3x3 array and check if each stage is a member of the abelian group
    for (int i = 0; i <= MAX_STABLE; i++) {
        abelian[0] = i;
        for (int j = 0; j <= MAX_STABLE; j++) {
            abelian[1] = j;
            for (int k = 0; k <= MAX_STABLE; k++) {
                abelian[2] = k;
                for (int l = 0; l <= MAX_STABLE; l++) {
                    abelian[3] = l;
                    for (int m = 0; m <= MAX_STABLE; m++) {
                        abelian[4] = m;
                        for (int n = 0; n <= MAX_STABLE; n++) {
                            abelian[5] = n;
                            for (int p = 0; p <= MAX_STABLE; p++) {
                                abelian[6] = p;
                                for (int q = 0; q <= MAX_STABLE; q++) {
                                    abelian[7] = q;
                                    for (int r = 0; r <= MAX_STABLE; r++) {
                                        abelian[8] = r;
                                        if (isInGroup()) {
                                            count++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return count;
}

string SandPile::toString() const {
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
