//
// Created by garci on 9/23/2020.
//

#ifndef P1X_P1X_TEST_H
#define P1X_P1X_TEST_H

/**
 * The main method is going to test the SandPileX class with 4 test arrays and
 * show the results.
 * @return will return 0 to indicate the program successfully completed
 */
int main();

/**
 * This method will run the SandPileX program using the array argument passed
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
 * This will check to make sure the totalAbelianGroups method is correctly
 * counting the Abelian sand piles.
 */
void testRecursiveAbelianCount();

#endif //P1X_P1X_TEST_H
