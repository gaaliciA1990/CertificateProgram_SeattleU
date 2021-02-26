#include <iostream>
#include <cmath>
#include "SandPileX.h"
#include "p1x_test.h"


using namespace std;

int main() {
    //Create a new instance of a sand pile array (default ctor)
    SandPileX *zeroCheck = new SandPileX();
    cout << "Zero (using no-arg ctor): " << zeroCheck->toString() << endl;
    delete zeroCheck;
    cout << endl; // Adding spacing format


    // initialize variables for the test arrays
    int stable1[] = {0, 0, 0, 0, 4, 0, 0, 0, 0};
    int stable2[] = {4, 0, 0, 0, 4, 0, 0, 0, 0};
    int stable3[] = {4, 0, 0, 0, 10, 0, 0, 0, 0};
    int stable4[] = {0, 6, 1, 0, 2, 0, 5, 1, 0};
    int stable5[] = {0, 0, 4, 0, 1, 0, 4, 0, 0};

    testPile(stable1);
    testPile(stable2);
    testPile(stable3);
    testPile(stable4);
    testPile(stable5);
    cout << endl; // Adding spacing format

    //initialize pile arrays for pile sum
    const int a1[] = {0, 0, 0, 0, 2, 0, 0, 0, 0};
    const int b1[] = {0, 0, 0, 0, 2, 0, 0, 0, 0};
    const int a2[] = {1, 2, 0, 2, 1, 1, 0, 1, 3};
    const int b2[] = {2, 1, 3, 1, 0, 1, 0, 1, 0};
    const int a3[] = {3, 3, 3, 3, 3, 3, 3, 3, 3};
    const int b3[] = {3, 3, 3, 3, 3, 3, 3, 3, 3};

    testAddPile(a1, b1);
    testAddPile(a2, b2);
    testAddPile(a3, b3);
    cout << endl; // Adding spacing format

    //Test values for isInGroup
    int three[] = {3, 3, 3, 3, 3, 3, 3, 3, 3};
    int two[] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
    int one[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    int zeros[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int group1[] = {3, 2, 2, 2, 1, 1, 3, 3, 3};
    int group2[] = {1, 2, 1, 2, 1, 2, 1, 1, 1};

    testInGroup(three);
    testInGroup(two);
    testInGroup(one);
    testInGroup(zeros);
    testInGroup(group1);
    testInGroup(group2);
    cout << endl; // Adding spacing format

    testRecursiveAbelianCount();
    cout << endl;
    return 0;
}

void testPile(const int *test) {
    // Creating a new instance of the SandPileX class with constructor
    SandPileX *abelianGroup = new SandPileX(test);

    cout << "Test before stabilization: " << abelianGroup->toString();
    abelianGroup->stabilize();
    cout << " After: " << abelianGroup->toString() << endl;
    delete abelianGroup;
}

void testAddPile(const int *a, const int *b) {
    // Creating instances of the SandPileX class with constructor for a, b,
    // and the sum
    SandPileX *pile1 = new SandPileX(a);
    SandPileX *pile2 = new SandPileX(b);
    SandPileX *sum = new SandPileX();

    cout << "a: " << pile1->toString() << "  b: " << pile2->toString();
    sum->addPile(pile1->abelian, pile2->abelian);
    cout << "  a + b = " << sum->toString() << endl;

    delete pile1;
    delete pile2;
}

void testInGroup(const int *test) {
    SandPileX *a = new SandPileX(test);

    if (a->isInGroup()) {
        cout << "The sand pile " << a->toString() << " is a member of the "
                                                     "Abelian group." << endl;
    }
    else {
        cout << "The sand pile " << a->toString() << " is not a member of the"
                                                     " Abelian group." << endl;
    }
    delete a;
}

void testRecursiveAbelianCount() {
    //Show the total number of possible sand piles in the Abelian group.
    SandPileX *validGroup = new SandPileX();

    cout << "Sand piles in the Abelian group: " <<
    validGroup->recursiveTotalAbelians(0) << endl;
    cout << "Out of total 3x3 sand piles: " << pow(SandPileX::MAX_STABLE + 1,
                                                   SandPileX::SIZE) <<
    endl;

    delete validGroup;
}