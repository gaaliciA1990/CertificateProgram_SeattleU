/*
 * Alicia Garcia
 * CPSC 5002, Seattle University
 * This is free and unencumbered software released into the public domain.
 */

package agarcia3_p2;

import java.io.File;
import java.io.IOException;
import java.util.Scanner;

/**
 * This program will ask the user for the file with the secret message and
 * calls methods from the MessageDocoder class to decode it. The message is
 * printed for the user. The user can repeat the program as many times as
 * they wish.
 *
 * @author Alicia Garica
 * @version 1.0
 */
public class SecretMessage {

    /**
     * This method prints a short description of the program for the user.
     */
    public static void welcome() {
        System.out.println("\nThis program reads an encoded message from a " +
                "file supplied by the user and\ndisplays the contents of the " +
                "final decoded message.\n");
    }

    /**
     * This method gets the file name with the encoded message from the user.
     * The file name is verified to be valid by calling the isValidFile method.
     *
     * @param keybd Scanner object for inputting text.
     * @return the fileName entered by the user.
     */
    public static String getFile(Scanner keybd) {
        String fileName;

        do {
            System.out.print("Enter the secret file name: ");
            fileName = keybd.nextLine();
        } while (!isValidFile(fileName));
        return fileName;
    }

    /**
     * Checks to see that the user-specified file name refers to a valid
     * file on the disk and not a directory. Displays an error message to the
     * user if that is not the case.
     *
     * @param fileName file name string to check.
     * @return true if file exists on disk and is not a directory.
     */
    private static boolean isValidFile(String fileName) {
        File path = new File(fileName);

        boolean isValid = path.exists() && !path.isDirectory();
        if (!isValid) {
            System.out.println("That is not a valid file name, please try " +
                    "again.");
        }
        return isValid;
    }

    /**
     * This method will ask the user if they'd like to play again and
     * return the player's answer. If the user presses enter, the question
     * will be asked again. If the user enters something other than no, or an
     * approved yes equivalent, the question will be asked again.
     *
     * @param keybd Scanner instance from main method.
     * @return the user answer in a char variable.
     */
    public static char repeatGame(Scanner keybd){
        char answer;

        // input string for repeat question to compare values entered
        String input;

        do {
            System.out.print("\nWould you like to try again? (No to exit): ");
            input = keybd.nextLine().toLowerCase();
        } while (input.length() < 1 || repeatAnswers(input) == null);
        answer = input.charAt(0);
        return answer;
    }

    /**
     * This method will check the answer entered by the user to determine if
     * the user wants to proceed or not. Given the nature of yes and no, the
     * responses are hardcoded with the most common nomenclatures for them in
     * order to loop the program. If they input no, no is returned, else null
     *
     * @param answer The user's inputted answer in the repeat method.
     * @return The final answer determined based on the approved responses.
     */
    private static String repeatAnswers(String answer) {
        return switch (answer) {
            case "yes", "sure", "yeah", "yep", "okay" -> "yes";
            case "no", "nah", "nope" -> "no";
            default -> null;
        };
    }

    /**
     * This method prints the goodbye message to the user.
     */
    public static void goodbye() {
        System.out.println("\nThank you for using the message decoder.");
    }

    /**
     * The main method will ask the user for the filename and read the file.
     * The file is read once and decoded based on the key. The final message
     * is printed to the user. The user can repeat this program as many times
     * as they would like.
     *
     * @param args  A string array containing the command line arguments.
     * @throws IOException program will crash if error not addressed by my
     *                     code is encountered.
     */
    public static void main(String[] args) throws IOException {
        String fileSecretMessage, messageDecoded;
        final char YES = 'y';
        char repeat;

        Scanner keybd = new Scanner(System.in);
        welcome();
        do {
            // ask for the file name
            fileSecretMessage = getFile(keybd);
            // Create an instance of the MessageDecoder object
            MessageDecoder decoder = new MessageDecoder();
            // Read the file and decrypt the message
            decoder.readFile(fileSecretMessage);
            System.out.println(decoder.getPlainTextMessage());
            repeat = repeatGame(keybd);
        } while (repeat == YES);
        keybd.close();
        goodbye();
    }
}
