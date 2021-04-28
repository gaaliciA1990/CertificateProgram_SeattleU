/**
 * Author: Alicia Garcia
 * Version: 1.0
 * Date: 4/20/2021 19:18
 */

package SubStringSearch;

/**
 * This class will search for a substring within a given string or sentence and return the first occurrence of the
 * substring found within the main string.
 */
public class SubstringSearch {
    // variables for the string to be searched and tracking the index if found
    String searchString;
    int foundIndex;

    /**
     * This is the constructor for the class that will instantiate our string to search through
     *
     * @param strg The string to be searched to find the substring
     */
    SubstringSearch(String strg) {
        searchString = strg;
    }

    /**
     * This method is iterating through the string to find a match with the substring. If a match is found, then we
     * begin iterating through the substring and comparing against the main string from index i. If the substring
     * doesn't match the main string from index i + j, then we break and move on to the next character in the main
     * string to test again.
     *
     * @param sub The substring to search for
     * @return the index where the found substring starts, else -1
     */
    public int searchString(String sub) {
        // Iterate through the string and compare char[i] and with the substring char[0]
        for (int i = 0; i < searchString.length(); i++) {
            if (searchString.charAt(i) == sub.charAt(0)) {
                foundIndex = i;
                // If the characters match, begin iterating through the substring and compare to
                // string char starting at i+j
                for (int j = 1; j < sub.length(); j++) {
                    if (sub.charAt(j) != searchString.charAt(i + j)) {
                        //If the chars are not equal, reset foundIndex and break out of the for loop
                        foundIndex = -1;
                        break;
                    }
                }
                // If the substring was found, return the index the substring found
                if (foundIndex != -1) {
                    return foundIndex;
                }
            }
        }
        return -1;
    }
}
