/*
 * Alicia Garcia
 * CPSC 5002, Seattle University
 * This is free and unencumbered software released into the public domain.
 */
package agarcia3_P3XC;

/**
 * The PlayerQueue class will store elements of the players cards (hand)
 * for playing the card game. This is using a Linked List structure and
 * Generics.
 *
 * @author Alicia Garcia
 * @version 1.0
 */
public class PlayerQueue<T> {

    /**
     * Inner Node class for creating the link list.
     */
    private class Node {
        Node next, prev;
        T value;

        /**
         * The inner class constructor.
         *
         * @param com The command value from the enum list
         * @param n   The next element in the queue
         * @param p   The previous element in the queue
         */
        public Node(T com, Node n, Node p) {
            value = com;
            next = n;
            prev = p;
        }
    }
    // Variables for the beginning and end of the queue
    private Node front;
    private Node rear;

    /**
     * The constructor for the PlayerQueue class
     */
    public PlayerQueue() {
        front = null;
        rear = null;
    }

    /**
     * This method will determine if the queue is empty.
     *
     * @return true if the queue is empty, else false.
     */
    public boolean empty() {
        return front == null;
    }

    /**
     * This method will add new elements from the parameter passed through to
     * the queue and build the pointers for each direction.
     *
     * @param card The card held in the players hand
     */
    public void enqueue(T card) {
        if (rear != null) {
            Node placeHolder = new Node(card, rear, null);
            rear.prev = placeHolder;
            rear = placeHolder;
        }
        else {
            rear = new Node(card, null, null);
            front = rear;
        }
    }

    /**
     * This method will remove an element from the queue's front and set the
     * front to the previous element (technically the next).
     *
     * @return The card from the players hand.
     */
    public T dequeue() {
        T card; // variable for the card

        if (empty()) {
            throw new RuntimeException("Empty hand found!");
        }
        else {
            card = front.value;
            front = front.prev;
            if (front == null) {
                rear = null;
            }
        }
        return card;
    }

    /**
     * This method will create a deep copy of the queue into a new instance
     * queue.
     *
     * @return the copied queue
     */
    public PlayerQueue<T> copy() {
        Node pos = front;
        // Create an instance of a new queue to copy to
        PlayerQueue<T> playerHand = new PlayerQueue<>();

        while (pos != null) {
            playerHand.enqueue(pos.value);
            pos = pos.prev;
        }
        return playerHand;
    }

    /**
     * This method will add the elements from another queue passed through to
     * the existing queue we have created. The original queue is not modified
     * in any way, instead, we create a deep copy of the elements and append
     * them to the queue we have created.
     *
     * @param newCard The queue to be appended to our created queue.
     */
    public void append(PlayerQueue<T> newCard) {
        // Create a new copy of the queue.
        PlayerQueue<T> newHand = newCard.copy();

        while (!newHand.empty()) {
            T playerHand = newHand.dequeue();
            enqueue(playerHand);
        }
    }

    /**
     * This method will check the value at the front of the queue.
     *
     * @return the value in the queue.
     */
    public T peek() {
        if (empty()) {
            throw new IllegalArgumentException("Player hand is empty!");
        }
        else {
            return front.value;
        }
    }

    /**
     * This method will compare two stacks to each other to determine if they
     * are equal.
     *
     * @param hand The queue to be compared to our created stack.
     * @return true if the queues are equal, else false
     */
    public boolean equals(PlayerQueue<Integer> hand) {
        PlayerQueue<Integer> copyHand = hand.copy();

        Node pos = front;
        while (pos != null) {
            Object copyPos = copyHand.dequeue();
            if (!pos.value.equals(copyPos)) {
                return false;
            }
            pos = pos.next;
        }
        return true;
    }

    /**
     * This method will print the queue for the player to see
     *
     * @return the full string of cards.
     */
    public String toString() {
        StringBuilder strBuilder = new StringBuilder();

        Node pos = front;
        while (pos != null) {
            strBuilder.append(pos.value);
            pos = pos.prev;
            if (pos != null) {
                strBuilder.append(" | ");
            }
        }
        return strBuilder.toString();
    }
}
