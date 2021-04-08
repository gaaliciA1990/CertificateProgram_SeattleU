/**
 * Author: Alicia Garcia
 * Version: 1.0
 * Date: 4/5/2021 19:12
 * Class: Seattle University
 * This is free and unencumbered software released into the public domain
 */


package HW1;

/**
 * Base class for all fibonacci classes holding key values, constructor, and get additionCount
 */
public class FibonacciBase {
    // Variables used across all Fibonacci child classes
    protected int fibStart;
    protected int A = 0, B = 1;
    protected int additionCounter = 0;


    /**
     * This is the constructor method. Here we will check to make sure the number isn't less
     * than 0 and assign it to our private variable.
     *
     * @param number The value entered by the user
     * @throws IllegalArgumentException if the number is less than 0, as we don't work with negative
     *                                  numbers for the fibonacci sequence
     */
    FibonacciBase(int number) {
        if (number < 0) {
            throw new IllegalArgumentException("Negative values are not supported." +
                    " Please enter a positive value");
        }
        fibStart = number;
    }

    /**
     * This will get the final count of additions run within the Fibonacci Sequence
     *
     * @return final additionCounter value
     */
    public int getCount() {
        return additionCounter;
    }
}
