#include <iostream>
#include <cmath>
#include "SandPile.h"
#include "p1_test.h"


using namespace std;

int main() {

    testZero();

    // initialize variables for the test arrays
    int stable1[] = {0, 0, 0, 0, 4, 0, 0, 0, 0};
    int stable2[] = {4, 0, 0, 0, 4, 0, 0, 0, 0};
    int stable3[] = {4, 0, 0, 0, 10, 0, 0, 0, 0};
    int stable4[] = {4, 4, 4, 10, 10, 0, 22, 1, 5};
    int stable5[] = {4, 4, 0, 0, 10, 0, 0, 0, 0};

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

    // Test the copy ctor: copy stable4 to Magic Pile
    testCopyCtor(stable4);
    cout << endl; // Adding spacing format


    //Test the operator method to ensure the assigned operator overload is
    // working: set group2 equal to a temp pile
    testAssignmentOperatorOL(group2);
    cout << endl; // Adding spacing format

    // Test the count possible Abelian Groups
    testCountGroups();
    cout << endl;
    return 0;
}

void testZero() {
    //Create a new instance of a sand pile array (default ctor)
    SandPile *zeroCheck = new SandPile();

    cout << "Zero (using no-arg ctor): " << zeroCheck->toString() << endl;

    delete zeroCheck;
    cout << endl; // Adding spacing format
}

void testPile(const int *test) {
    // Creating a new instance of the SandPile class with constructor
    SandPile *abelianGroup = new SandPile(test);

    cout << "Test before stabilization: " << abelianGroup->toString();
    abelianGroup->stabilize();
    cout << " After: " << abelianGroup->toString() << endl;
    delete abelianGroup;
}

void testAddPile(const int *a, const int *b) {
    // Creating instances of the SandPile class with constructor for a, b,
    // and the sum
    SandPile *pile1 = new SandPile(a);
    SandPile *pile2 = new SandPile(b);
    SandPile *sum = new SandPile();

    cout << "a: " << pile1->toString() << "  b: " << pile2->toString();
    sum->addPile(pile1->abelian, pile2->abelian);
    cout << "  a + b = " << sum->toString() << endl;
    delete pile1;
    delete pile2;
}

void testInGroup(const int *test) {
    SandPile *a = new SandPile(test);

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

void testCopyCtor(const int *test) {
    SandPile *initialPile = new SandPile(test);
    cout << "Initial pile to be copied: " << initialPile->toString() << endl;

    SandPile *copied = new SandPile(initialPile);
    cout << "Copying completed! Here's your Magic Pile: " <<
         copied->toString() << endl;

    delete initialPile;
    delete copied;
}

void testAssignmentOperatorOL(const int *test) {
    SandPile *initialPile = new SandPile(test);
    cout << "Initial pile to be set equal to temp: " << initialPile->toString()
         << endl;

    SandPile *temp = new SandPile();
    *temp = initialPile;
    cout << "Now temp, " << temp->toString() << ", is equal to initial pile, "
         << initialPile->toString() << endl;

    delete initialPile;
    delete temp;
}

void testCountGroups() {
    SandPile *validGroup = new SandPile();

    cout << "Sand piles in the Abelian group: " <<
         validGroup->totalAbelianGroups()
         << endl;

    cout << "Out of total " << SandPile::DIM << "x" << SandPile::DIM << "sand"
                                                                        "piles: "
         << pow(SandPile::MAX_STABLE + 1, SandPile::DIM * SandPile::DIM)
         << endl;

    delete validGroup;
}
