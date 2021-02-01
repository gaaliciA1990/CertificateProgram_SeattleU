/*
 * Author: Scott McMaster, Alicia Garcia
 * Version: 2.0
 * Date: 1/13/21
 * Class: CPSC 5011-02
 */

package hw1;

import java.io.FileNotFoundException;
import java.util.Map;

/**
 * This class will create the final message displayed to the user based
 * on the translations from words beginning with $.
 */
public class Template {
    private String[] words; // array to hold the words from the message
    private String file = "yow.lines";

    /**
     * A Constructor to delimit the words by whitespaces
     *
     * @param s The message with key values
     */
    public Template(String s) {
        // This will delimit the words based on whitespace.
        // Double slash is required to escape the character.
        words = s.split("\\s");
    }

    /**
     * This method will translate the words that contact a $ at pos[0] based on either daypart
     * or the user indicated hashmap. Once all words have been translated, the message
     * is returned.
     * @param args The dictionary that is passed through the instance
     * @return The translated message from the template
     */
    public String instantiate(Map<String, String> args) throws FileNotFoundException {
        // Create an array of words to hold the words from the message
        String[] translatedWords = new String[words.length];
        Zippy zip = new Zippy(file);

        // iterate through the message and translate the necessary words per their requirements.
        for (int i = 0; i < words.length; i++) {
            if (isVariable(words[i])) {
                if (words[i].equals("$daypart"))
                    translatedWords[i] = (new DayPart()).toString();
                else if (words[i].equals("$zippy")) {
                    translatedWords[i] = zip.randomZippyGen();
                }
                else if (words[i].equals("$newline")) {
                    translatedWords[i] = "\n";
                }
                else if (args.containsKey(words[i]))
                    translatedWords[i] = args.get(words[i]);
            } else {
                translatedWords[i] = words[i];
            }
        }
        return String.join(" ", translatedWords);
    }

    /**
     * This method will verify if the first character is a $
     *
     * @param s The word to check the first character of
     * @return True is charAt(0) = $, else false
     */
    private boolean isVariable(String s) {
        return s.charAt(0) == '$';
    }
}
