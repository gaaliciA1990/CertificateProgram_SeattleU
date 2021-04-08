/**
 * Author: Alicia Garcia
 * Version: 1.0
 * Date: 4/5/2021 18:57
 * Class: Seattle University 5031-02
 * This is free and unencumbered software released into the public domain
 */


package HW1;

/**
 * This class will run the 3 types of addition operations for the fibonacci sequence. The output is the table
 * that shows the value to be computed, the solution of f(n) and the total number of additions performed
 * for each object.
 */
public class FibonacciSequence {
    /**
     * The main method to initialize the Fibonacci objects and run the calculations to print
     *
     * @param args The string argument from the command line
     */
    public static void main(String[] args) {
        final int A = 0, B = 1;
        int num = 3;
        int num2 = 10;
        int num3 = 20;

        System.out.println("Value\t  fib(n)\tClassic Recursive\tIterative\tRecursive w/Accum");
        System.out.println("--------------------------------------------------------------------");

        initializeFibObjects(num);
        initializeFibObjects(num2);
        initializeFibObjects(num3);

    }

    /**
     * This method will initialize the Fibonacci objects and calculate the fibonacci sequence for each value of n and
     * print the table for fib(n) and the addition counts for each solution technique
     *
     * @param n The value to solve the Fibonacci sequence for
     */
    public static void initializeFibObjects(int n) {
        IterativeFib itFib = new IterativeFib(n);
        ClassicRecurFib classFib = new ClassicRecurFib(n);
        AccumulatorRecurFib accFib = new AccumulatorRecurFib(n);

        int fibN = solverFibSeq(itFib, classFib, accFib);
        printFib(n, fibN, itFib, classFib, accFib);
    }

    /**
     * This method will call the FibonacciSeq method to solve the fib(n) for each solution technique. The values are
     * compared to each other to verify they are equal. The value of fib(n) is return if all are equal, other a -1
     *
     * @param itFib    The iterative fibonacci technique object
     * @param classFib The classic recursive fibonacci technique object
     * @param accFib   The recursive with accumulator fibonacci technique object
     * @return the value of fib(n) if all 3 solutions are equal, else -1 to show they aren't equal.
     */
    public static int solverFibSeq(IterativeFib itFib, ClassicRecurFib classFib, AccumulatorRecurFib accFib) {
        int fibN1, fibN2, fibN3;

        fibN1 = itFib.FibonacciSeq();
        fibN2 = classFib.FibonacciSeq();
        fibN3 = accFib.FibonacciSeq();

        if (fibN1 == fibN2 && fibN2 == fibN3) {
            return fibN1;
        }
        return -1;
    }

    /**
     * This method will print the solutions for each calculation in a formatted output
     *
     * @param n        The value to solve the Fibonacci sequence for
     * @param fibN     The solution for the Fibonacci sequence
     * @param itFib    The iterative fibonacci technique object
     * @param classFib The classic recursive fibonacci technique object
     * @param accFib   The recursive with accumulator fibonacci technique object
     */
    public static void printFib(int n, int fibN, IterativeFib itFib, ClassicRecurFib classFib,
                                AccumulatorRecurFib accFib) {
        System.out.printf("n = %-8d%-13d%-18d%-12d%-10d", n, fibN, classFib.getCount(), itFib.getCount(),
                accFib.getCount());
        System.out.println();
    }
}
