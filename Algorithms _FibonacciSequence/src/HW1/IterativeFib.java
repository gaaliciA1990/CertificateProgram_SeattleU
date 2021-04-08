/**
 * Author: Alicia Garcia
 * Version: 1.0
 * Date: 4/5/2021 18:58
 * Class: Seattle University
 * This is free and unencumbered software released into the public domain
 */


package HW1;

/**
 * This class extends the FibonnaciBase class and implements the iterative solution for
 * solving the Fibonacci Sequence
 */
public class IterativeFib extends FibonacciBase {

    /**
     * The constructor method
     *
     * @param number The value to solve the Fibonacci sequence for, fibStart
     */
    IterativeFib(int number) {
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
     * This method will iteratively solve the equation for Fibonacci Sequence.
     *
     * @return The solution for fib(n)
     */
    private int FibonacciSolver(int n) {
        if (n == 0 || n == 1) {
            return n;
        }

        int C = 0;
        for (int i = 2; i <= n; i++) {
            C = B + A;
            A = B;
            B = C;
            additionCounter++;
        }
        return C;
    }

}
