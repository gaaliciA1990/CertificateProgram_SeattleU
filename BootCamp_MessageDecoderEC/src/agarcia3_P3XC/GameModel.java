/*
 * Alicia Garcia
 * CPSC 5002, Seattle University
 * This is free and unencumbered software released into the public domain.
 */
package agarcia3_P3XC;

import java.util.ArrayList;
import java.util.Random;

/**
 * This class creates the body of the card game. Here the deck is create and
 * shuffled, then the player queues are created and filled with 7 cards per
 * player. The game is initiated with a deal deck card and the player cards
 * are compared to the discard pile.
 *
 * @author Alicia Garcia
 * @version 1.0
 */
public class GameModel {
    // variables for the class
    private ArrayList<Integer> deck;
    private CardStack<Integer> dealDeck = new CardStack<>();
    private CardStack<Integer> discardPile = new CardStack<>();

    /**
     * Class constructor. The deck is set to a new ArrayList
     */
    public GameModel() {
        deck = new ArrayList<>();
    }

    /**
     * This method will create the player queues to hold their cards
     * throughout the game.
     *
     * @param names player names to assign the queue to.
     * @return an ArrayList of Queues
     */
    public ArrayList<PlayerQueue<Integer>> players(ArrayList<String> names) {
        ArrayList<PlayerQueue<Integer>> numPlayers = new ArrayList<>();

        for (int i = 0; i < names.size(); i++) {
            numPlayers.add(new PlayerQueue<Integer>());
        }
        return numPlayers;
    }

    /**
     * This method will create the deck as an ArrayList. It holds 52 cards,
     * with 4 sets numbered 1-13
     */
    public void createNewDeck() {
        final int DECK = 4;
        final int CARDS = 13;

        for (int i = 0; i < DECK; i++) {
            for (int j = 1; j <= CARDS; j++) {
                deck.add(j);
            }
        }
    }

    /**
     * This method will shuffle the cards of the ArrayList deck so they are
     * in a random order.
     */
    private void shuffleDeck() {
        Random rand = new Random();

        for (int i = deck.size(); i > 1; i--) {
            int pos = rand.nextInt(i);
            int temp = deck.get(i - 1);
            deck.set(i - 1, deck.get(pos));
            deck.set(pos,temp);
        }
    }

    /**
     * This method will create the deal deck in a stack,
     */
    private void initializeDealDeck() {
        for (Integer integer : deck) {
            dealDeck.push(integer);
        }
    }

    /**
     * This method will set up the game by shuffling the deck and storing the
     * cards in the deck Stack. Then 1 card is pushed to the discard pile to
     * begin the game for the players.
     */
    public void initiateGame() {
        shuffleDeck();
        initializeDealDeck();
        // Add 1 card to the discard pile to initialize the game for the
        // players to compare their card against in the first round
        discardPile.push(dealDeck.pop());
    }

    /**
     * This method will deal the cards to the players and store the cards in
     * their respective queues.
     *
     * @param playerHands The players cards they will start our with.
     */
    public void dealCards(ArrayList<PlayerQueue<Integer>> playerHands) {
        final int HAND = 7;

        for (int i = 0; i < HAND; i++) {
            for (PlayerQueue<Integer> playerHand : playerHands) {
                playerHand.enqueue(dealDeck.pop());
            }
        }
    }

    /**
     * This method is called when the deal deck is empty. The top card of the
     * discard pile is removed, then the remaining cards are pushed to the
     * deal deck (in reverse order now). The removed top card is added back
     * to the discard pile for the next player to compare their card to.
     */
    private void changeDeck() {
        int top = discardPile.pop();
        while (!discardPile.empty()) {
            dealDeck.push(discardPile.pop());
        }
        discardPile.push(top);
    }

    /**
     * This method will check if the deal deck is empty, and call the
     * changeDeck method to fill it back up.
     */
    private void emptyDeck() {
        if (dealDeck.empty()) {
            changeDeck();
        }
    }

    /**
     * This method will compare the players card to the discard pile and
     * execute the correct action based on the results.
     *
     * @param playerHand The card the player is holding to compare against.
     */
    public void checkCards(PlayerQueue<Integer> playerHand) {
        System.out.println("Discard pile card: " + discardPile.peek());
        System.out.println("Your played card: " + playerHand.peek());

        if (playerHand.peek().equals(discardPile.peek())) {
            System.out.println("So close! You almost got 'im. Your card" +
                    " is equal\nto the discard pile card. Not the worst, but " +
                    "not a\nwinner...pick up 1 card.\n");
            discardPile.push(playerHand.dequeue());
            emptyDeck();
            playerHand.enqueue(dealDeck.pop());
        }
        else if (playerHand.peek() < discardPile.peek()) {
            System.out.println("Bummer! Your card is LOWER than the discard\n" +
                    "pile card. How'd that happen? Are you even trying?\n" +
                    "Pick up two cards!\n");
            discardPile.push(playerHand.dequeue());
            final int PENALTY = 2;
            for (int i = 0; i < PENALTY; i++) {
                emptyDeck();
                playerHand.enqueue(dealDeck.pop());
            }
        }
        else {
            discardPile.push(playerHand.dequeue());
            System.out.println("What?! That's amazing! How'd you do that?" +
                    " Congrats,\nyour card HIGHER than the " +
                    "discard pile card!\nNo punishment..this time. Next " +
                    "player, come on up!\n");
        }
        emptyDeck();
    }
}
