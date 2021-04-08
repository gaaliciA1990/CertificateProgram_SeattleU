/**
 * Author: Alicia Garcia
 * Version: 1.0
 * Date: 4/5/2021 18:57
 * Class: Seattle University
 * This is free and unencumbered software released into the public domain
 */


package HW1;

/**
 * This class extends the FibonnaciBase class and implements the classic recursive solution for
 * solving the Fibonacci Sequence
 */
public class ClassicRecurFib extends FibonacciBase {
    /**
     * The constructor method
     *
     * @param number The value to solve the Fibonacci sequence for, fibStart
     */
    ClassicRecurFib(int number) {
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

        return FibonacciSolver(fibStart);
    }

    /**
     * This method is recursively solving the fib(n), following the standard equation for the Fibonacci sequence.
     *
     * @param n The value to solve the Fibonacci sequence for, fibStart
     * @return The solution for fib(n)
     */
    private int FibonacciSolver(int n) {
        if (n <= 1) {
            return n;
        }
        additionCounter++;
        return FibonacciSolver(n - 1) + FibonacciSolver(n - 2);
    }
}
