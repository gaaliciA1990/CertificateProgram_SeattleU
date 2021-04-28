/**
 * Author: Alicia Garcia
 * Version: 1.0
 * Date: 4/21/2021 19:09
 * Class: Seattle University
 * This is free and unencumbered software released into the public domain
 */


package SubStringSearch;

/**
 * This is our main launcher for implementing the Substring Search program
 */
public class ProgramLauncher {
    /**
     * This is the main method that will return the results of the Substring search and initialize the test cases
     *
     * @param args The string argument from the command line
     */
    public static void main(String[] args) {
        // Creating two arrays to hold our test sentences and substrings
        String[] testCase = {"Happy happy joy joy", "Where is the dog", "fun fun fun", "I love coding!"};
        String[] subString = {"happy", "cat", "fun", "Me too!"};

        printResults(testCase, subString);
    }

    /**
     * This method will iterate through the test Strings and target substrings and print the results of the substring
     * search.
     *
     * @param testCases Array holding our test sentences to search through
     * @param subString Array holding our substrings to search through it's corresponding testCase
     */
    public static void printResults(String[] testCases, String[] subString) {
        for (int i = 0; i < testCases.length; i++) {
            SubstringSearch search = new SubstringSearch(testCases[i]);
            System.out.println("String:" + testCases[i]);
            System.out.println("Substring: " + subString[i]);
            System.out.println("Result:" + search.searchString(subString[i]));
            System.out.println();
        }
    }

}
