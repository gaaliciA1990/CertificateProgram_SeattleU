//
// Created by garci on 9/23/2020.
//
#include <iostream>

#ifndef P1X_SANDPILEX_H
#define P1X_SANDPILEX_H

/**
 * This class implements the functionality of a sand pile, technically of
 * any size. This class has a ctor, copy ctor, dstor and assigned operator
 * overload. It validates if a sand pile is a member of the Abelian group,
 * adds two sand piles togethers, checks for unstable sand piles, stabilizes
 * unstable sand piles and counts the total number of valid Abelian sand
 * piles possibles. This class also has its own toString function.
 */

//Identity (ZERO) sand pile
constexpr static const int ZERO[] = {2, 1, 2, 1, 0, 1, 2, 1, 2};

class SandPileX {
public:
    static const int MAX_STABLE = 3; //The max number of "grains" in a cell
    static const int DIM = 3; //The width of array (3x3)
    int *abelian; //Creating a dynamic pointer Sandpile array variable

    /**
     * Default ctor for Sandpile object (zero/Identity)
     */
    SandPileX();

    /**
     * Ctor for our Sandpile object that accepts an int argument
     * @param pile
     */
    SandPileX(const int *pile);

    /**
     * The copy ctor for Sandpile object, that passes an object of the same
     * class without modifying it
     * @param pile is the object to be copied
     */
    SandPileX(const SandPileX *copy);

    /**
    * The assignment operator overloading method will copy all of the
    * elements from one pile into our default abelian object
    * @param other the sand pile object to be copied
    * @return the point to the current object
    */
    SandPileX& operator= (const SandPileX &other);

    /**
     * The destor for the Sandpile object
     */
    ~SandPileX();

    /**
    * Set the values of each cell in this sand abelian.
    * @param cells 1st row elements, then 2nd, etc., all in one flat array
    */
    void setPile(const int *cells);

    /**
     * Checks if the Sandpile is in the Abelian group (262,144) or not
     * @return true if the Sandpile is in the group, else false
     */
    bool isInGroup();

    /**
     * Adds the Sandpile arrays a and b together
     * @param a the first sandpile array pointer
     * @param b the second sandpile array pointer
     * @return the sum of the Sandpiles as an array
     */
    int *addPile(const int *a, const int *b);

    /**
     * Is this sand abelian stable or will it topple?
     * I.e., if there are any cells over 3 (SandPileX::MAX_STABLE) then it will
     * topple.
     * @return true if it won't topple, false if it will
     */
    bool isStable() const;

    /**
     * Topple this sand pile until it is stable (according to toppling rules).
     * Each unstable cell spills one grain of sand in each direction. If they
     * fall off the edge that's ok.
     */
    void stabilize();

    /**
     * Counts the all valid members of the abelian group and returns the
     * total count of valid members, using recursion.
     * @return the total number in abelian group
     */
    int recursiveTotalAbelians(int index);

    /**
    * Get a string suitable for printing out.
    * @return a 3-line string with the contents of this sand abelian
    */
    std::string toString() const;

private:
    static const int SIZE = DIM * DIM; //The size of the flat array
    
    //used to map rows/cols index to flat array
    static int index(int row, int col);

};

#endif //P1X_SANDPILEX_H
