//
// Created by garci on 9/20/2020.
//

#ifndef LAB1_P1_TEST_H
#define LAB1_P1_TEST_H

/**
 * The main method is going to test the SandPile class with 4 test arrays and
 * show the results.
 * @return will return 0 to indicate the program successfully completed
 */
int main();

/**
 * This method will demonstrate the no-arg ctor
 */
void testZero();

/**
 * This method will run the SandPile program using the array argument passed
 * trough it.
 * @param test The array to conduct the stabilization on, if needed.
 */
void testPile(const int *test);

/**
 * This method will pass two sand piles to test the addPile method from
 * SandPiles class.
 * @param a the first pile array to sum with
 * @param b the second pile array to sum with
 */
void testAddPile(const int *a, const int *b);

/**
 * This method will test whether an given sand pile is a valid member of the
 * Abelian Group
 * @param test the test array for testing
 */
void testInGroup(const int *test);

/**
 * This method will test the functionality of the copy ctor
* @param test The pile to be copied
 */
void testCopyCtor(const int *test);

/**
 * This method will test the functionality of the assignment operator overload
 * method
 * @param test The pile to be copied
 */
void testAssignmentOperatorOL(const int *test);

/**
 * This will check to make sure the totalAbelianGroups method is correctly
 * counting the Abelian sand piles.
 */
void testCountGroups();

#endif //LAB1_P1_TEST_H