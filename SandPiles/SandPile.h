//
// Created by garci on 9/14/2020.
//
#include <iostream>

#ifndef LAB1_SANDPILE_H
#define LAB1_SANDPILE_H

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

class SandPile {
public:
    static const int MAX_STABLE = 3; //The max number of "grains" in a cell
    static const int DIM = 3; //The width of array (3x3)
    int *abelian; //Creating a dynamic pointer Sandpile array variable

    /**
     * Default ctor for Sandpile object. This will set the abelian variable
     * to the Zero/Identity sand pile.
     */
    SandPile();

    /**
     * Ctor for our Sandpile object that accepts an int argument
     * @param pile The pile array to be created
     */
    SandPile(const int *pile);

    /**
     * The copy ctor for Sand pile object, that passes an object of the same
     * class without modifying it
     * @param copy The object to be copied to a new temp pile
     */
    SandPile(const SandPile *copy);

    /**
     * The assignment operator overloading method will copy all of the
     * elements from one pile into our default abelian object
     * @param other The sand pile object to be copied
     * @return the point to the current object
     */
    SandPile &operator=(const SandPile &other);

    /**
     * The destor for the Sandpile object
     */
    ~SandPile();

    /**
    * Set the values of each cell in this sand abelian.
    * @param cells The 1st row elements, then 2nd, etc., all in one flat array
    */
    void setPile(const int *cells);

    /**
     * Checks if the Sand pile is in the Abelian group (262,144) or not
     * @return true if the Sand pile is in the group, else false
     */
    bool isInGroup();

    /**
     * Adds the Sandpile arrays a and b together
     * @param a The first sand pile array pointer
     * @param b The second sand pile array pointer
     * @return the sum of the Sand piles as an array
     */
    int *addPile(const int *a, const int *b);

    /**
     * Is this sand abelian stable or will it topple?
     * I.e., if there are any cells over 3 (SandPile::MAX_STABLE) then it will
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
     * total count of valid members
     * @returns the total members of the group (count)
     */
    int totalAbelianGroups();

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

#endif //LAB1_SANDPILE_H
