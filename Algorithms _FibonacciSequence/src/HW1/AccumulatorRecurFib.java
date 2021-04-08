/**
 * Author: Alicia Garcia
 * Version: 1.0
 * Date: 4/5/2021 18:58
 * Class: Seattle University
 * This is free and unencumbered software released into the public domain
 */


package HW1;

/**
 * This class extends the FibonnaciBase class and implements the improved recursive solution for
 * solving the Fibonacci Sequence
 */
public class AccumulatorRecurFib extends FibonacciBase {
    /**
     * The constructor method
     *
     * @param number The value to solve the Fibonacci sequence for, fibStart
     */
    AccumulatorRecurFib(int number) {
        super(number);
    }

    /**
     * This method will return the solution for the FibonacciSolver and resets the additionCounter to 0, in case the
     * method is called multiple times.
     *
     * @return The value of fib(n)
     */
    public int FibonacciSeq() {
        additionCounter = 0;

        return FibonacciSolver(fibStart, A, B);
    }

    /**
     * This method will recursively solve for the Fibonacci Sequence using an accumulator base state. This improves
     * on the classic recursive method
     *
     * @param n The value to solve the Fibonacci sequence for, fibStart
     * @param a Initial start value of 0 for setting the base case
     * @param b Initial start value of 1 for setting the base case
     * @return  The solution for fib(n)
     */
    private int FibonacciSolver(int n, int a, int b) {
        switch (n) {
            case 0:
                return a;
            case 1:
                return b;
            default:
                additionCounter++;
                return FibonacciSolver(n - 1, b, a + b);
        }
    }

}
