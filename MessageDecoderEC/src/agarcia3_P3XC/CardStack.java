/*
 * Alicia Garcia
 * CPSC 5002, Seattle University
 * This is free and unencumbered software released into the public domain.
 */
package agarcia3_P3XC;

/**
 * The CardStack class will store elements of the dealDeck and discard Deck
 * instances for playing the card game. This is using a Linked List structure
 * and Generics.
 *
 * @author Alicia Garcia
 * @version 1.0
 */
public class CardStack<T> {

    /**
     * This class will store the list elements and a reference to the next one.
     */
    private class Node {
        T value;
        Node next;

        /**
         * The constructor for the Node class.
         *
         * @param val The double number read from the String in RPN class.
         * @param n   The next element is the linked list.
         */
        public Node(T val, Node n) {
            value = val;
            next = n;
        }
    }

    // The variable for the top of the stack
    private Node top;

    /**
     * The constructor for the CardStack class.
     */
    public CardStack() {
        top = null;
    }

    /**
     * Checks if the stack is empty.
     *
     * @return true when the stack is empty, else false.
     */
    public boolean empty() {
        return top == null;
    }

    /**
     * This method will store the value in the stack.
     *
     * @param number  The value from the string equation.
     */
    public void push(T number) {
        top = new Node(number, top);
    }

    /**
     * This method will extract the value from the top of the stack. If the
     * stack is empty, an exception is thrown.
     *
     * @return  The element from the stack.
     */
    public T pop() {
        if (empty()) {
            throw new IllegalArgumentException("Dealer deck is empty!");
        }
        else {
            T retValue = top.value;
            top = top.next;
            return retValue;
        }
    }

    /**
     * This method will check the value at the top of the stack. If the stack
     * is empty, an exception is thrown.
     *
     * @return  The element at the top of the stack.
     */
    public T peek() {
        if (empty()) {
           throw new IllegalArgumentException("Deck is empty!");
        }
        else {
            return top.value;
        }
    }

    /**
     * This method will create a deep copy of the stack into a new instance
     * stack, in the correct order.
     *
     * @return the copied stack.
     */
    public CardStack<T> copy() {
        Node pos = top;
        // Create an instance of a new stack to copy to
        CardStack<T> copyDeck = new CardStack<>();

        while (pos != null) {
            copyDeck.push(pos.value);
            pos = pos.next;
        }
        // Create another instance of a stack and copy one more time to set
        // the values in the correct order.
        CardStack<T> newDeck = new CardStack<>();
        while (!copyDeck.empty()) {
            newDeck.push(copyDeck.pop());
        }
        return newDeck;
    }

    /**
     * This method will return the size of the stack that has been populated.
     * If empty, an exception is thrown.
     *
     * @return the count of the stack size.
     */
    public int size() {
        int count = 0;

        Node pos = top;
        if (empty()) {
            throw new IllegalArgumentException("Deck is empty!");
        }
        while (pos != null) {
            count++;
            pos = pos.next;
        }
        return count;
    }

    /**
     * This method will compare two stacks to each other to determine if they
     * are equal.
     *
     * @param deck The stack to be compared to our created stack.
     * @return true if the stacks are equal, else false
     */
    public boolean equals(CardStack<T> deck) {
        CardStack copyDeck = deck.copy();

        Node pos = top;
        while (pos != null) {
            Object copyPos = copyDeck.pop();
            if (!pos.value.equals(copyPos)) {
                return false;
            }
            pos = pos.next;
        }
        return true;
    }

    /**
     * This method will print the stack values.
     *
     * @return the String of the appended data.
     */
    public String toString() {
        StringBuilder strBuild = new StringBuilder();

        Node pos = top;
        while (pos != null) {
            strBuild.append(pos.value);
            pos = pos.next;
            if (pos != null) {
                strBuild.append(" | ");
            }
        }
        return strBuild.toString();
    }
}
