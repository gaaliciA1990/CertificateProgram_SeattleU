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
 * This class reads the secret message file and decodes the message using a
 * linked list. The decoded message is then printed to a string with a
 * toString method. This class holds the inner Node class for creating the
 * linked list. Any duplicates, missing chars/numbers or negative numbers
 * will be skipped by the decoder method.
 *
 * @author Alicia Garcia
 * @version 1.0
 */
public class MessageDecoder {
    /**
     * This class will store the list elements and a reference to the next one.
     */
    private class Node {
        int listOrder;
        char value;
        Node next;

        /**
         * The constructor for the Node class.
         *
         * @param order The number associated with the secret message.
         * @param val   The letter associated with the secret message.
         */
        public Node(int order, char val) {
            listOrder = order;
            value = val;
            next = null;
        }
    }

    // Variables for first and last nodes
    private Node first, last;

    /**
     *  constructor for the MessageDecoder class.
     */
    public MessageDecoder() {
        first = null;
        last = null;
    }

    /**
     * This method will read the file and populate the linked list decoded by
     * calling the decodeMessage method.
     *
     * @param fileName The file with the encrypted message, entered by the user.
     * @throws IOException will close the program for any unhandled errors
     *                     with the file.
     */
    public void readFile(String fileName) throws IOException {
        int number;
        char letter;

        File file = new File(fileName);
        Scanner inFile = new Scanner(file);

        while (inFile.hasNext()) {
            // Read each line as a string
            String value = inFile.nextLine();

            // Pull the first letter from the string and create a
            // subString of the numbers after the character. Then parse the new
            // string to an int value.
            if (value.length() >= 3) {
                if (value.charAt(1) == ' ') {
                    letter = value.charAt(0);
                    String subValue = value.substring(2);
                    number = Integer.parseInt(subValue);
                    // Pass the valid variables through the decoding method
                    decodeMessage(number, letter);
                }
            }
        }
        inFile.close();
    }


    /**
     * This method checks if the linked list is empty.
     *
     * @return  true if the list is empty, else false.
     */
    public boolean isEmpty() {
        return first == null;
    }

    /**
     * This method organizes the file contents into the correct order. The order
     * number is checked against the other order positions in the linked list
     * and the value (char) is populated into the list. If there is a duplicate
     * number, the second number is will be skipped. If there are errors in
     * the file (formatting off, missing number/char or a negative number),
     * they will be skipped.
     *
     * @param order The numeric value following the letter in the file.
     * @param value The letter in the file.
     */
    private void decodeMessage(int order, char value) {
        Node placeHolder;
        Node pred = first;
        final int LOWERBOUND = 0;

        // check if the order (number) from the file is less than 1 and
        // skip (break from the code)
        if (order <= LOWERBOUND) {
            return;
        }

        // Populates the first element when the linked list is empty
        if (isEmpty()) {
            first = new Node(order, value);
            last = first;
            return;
        }
        // Replaces the first element when the order is less than the order
        // currently present in that spot.
        if (order < first.listOrder) {
            placeHolder = new Node(order, value);
            placeHolder.next = first;
            first = placeHolder;
            return;
        }
        // Populates the last element when the order is greater than the
        // order currently present in that spot.
        if (order > last.listOrder) {
            placeHolder = new Node (order, value);
            last.next = placeHolder;
            last = placeHolder;
            return;
        }
        // Populates the linked list when the order is less than the
        // predecessor or places it at the end of the list. If the number is a
        // duplicate of the predecessor, it will be skipped
        while (pred != null) {
            if (order == pred.listOrder) {
                return;
            }
            else if (pred.next == null) {
                placeHolder = new Node(order, value);
                pred.next = placeHolder;
                return;
            }
            else if (order < pred.next.listOrder) {
                placeHolder = new Node(order, value);
                placeHolder.next = pred.next;
                pred.next = placeHolder;
                return;
            }
            pred = pred.next;
        }
    }

    /**
     * This will print the decoded message, using the stringBuilder function.
     *
     * @return  The final decoded string from the file.
     */
    public String getPlainTextMessage() {
        // Create new instance of StringBuilder
        StringBuilder strBuilder = new StringBuilder();

        Node p = first;
        // Add default message for decoded string
        strBuilder.append("Decoded Message: ");
        // Loop through each node in the linked list and append it to the
        // StringBuilding object
        while (p != null) {
            strBuilder.append(p.value);
            p = p.next;
        }
        return strBuilder.toString();
    }
}
