/*
 * Alicia Garcia
 * CPSC 5002, Seattle University
 * This is free and unencumbered software released into the public domain.
 */
package agarcia3_P3XC;

import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Scanner;
/**
 * This program will play a card game with 2-6 players. A deck of cards is
 * created with four sets of 1-13, then shuffled. The players are dealt 7
 * cards and 1 card is placed on the discard pile. The players will compare
 * their cards to the discard pile after each turn (each play discards their
 * card to the pile after their turn). The first player to get rid of their
 * hand wins. The game can be replayed multiple times.
 *
 * @author Alicia Garcia
 * @version 1.0
 */
public class SillyGamesXC {
    /**
     * This is a short description of the game for the user(s).
     */
    public static void welcome() {
        System.out.println("\nThis is a game made by Silly Little Games. In\n" +
                "this game, there are 2-6 players. The players will be\n" +
                "dealt seven cards to begin with. They will compare\n" +
                "their cards to to the discard pile and if their card is\n" +
                "not higher than the discard pile card, the player will\n" +
                "need to draw cards. The first player to clear their" +
                " hands wins!\n\nLet's begin!\n");
    }

    /**
     * This method will ask the user(s) for the number of players they want.
     * Only valid numbers are accepted and only numbers between 2 and 6.
     *
     * @param keybd Scanner object for accepting the user's input
     * @return the number of players in this game.
     */
    public static int  numPlayers(Scanner keybd) {
        int numPlayers = 0;

        do {
            System.out.print("Enter the number of players in your round: ");
            try {
                numPlayers = keybd.nextInt();
                keybd.nextLine(); // Clear the next line.
            }
            catch (InputMismatchException e) {
                System.out.println("That's not a number, let's try that again" +
                        ".");
                keybd.nextLine();   // Clear the next line
            }
        } while (numPlayers < 2 || numPlayers > 6);
        return numPlayers;
    }

    /**
     * This method will ask the user(s) for the player names and store them
     * in an Array List
     * @param keybd Scanner object to accept user inputs
     * @param names The ArrayList to store the player names
     */
    public static void playerNames(Scanner keybd, ArrayList<String> names,
                                   int numPlayers) {

        for (int i = 1; i <= numPlayers; i++) {
            System.out.print("Enter player " + i + "'s name: ");
            names.add(keybd.nextLine());
        }
        System.out.println();   //Add new line for formatting
    }

    /**
     * This method will run through the gameplay until a winner if found.
     * Once a winner is found, the player will be notified.
     *
     * @param game The GameModel object for running the game play.
     * @param players   The list of player names in the game.
     * @param hand  The cards held in each players hand.
     */
    public static void playGame(GameModel game, ArrayList<String> players,
                                ArrayList<PlayerQueue<Integer>> hand) {
        boolean winner = false;

        do {
            for (int i = 0; i < players.size(); i++) {
                System.out.println(players.get(i) + ", are you ready? Here " +
                        "is your hand: ");
                System.out.println(hand.get(i));
                game.checkCards(hand.get(i));
                // Check if the players hand is empty to determine if the
                // game should be ended
                if (hand.get(i).empty()) {
                    winner = true;
                    printWinner(players.get(i));
                    return;
                }
                winner = false;
            }
        } while (!winner);
    }

    /**
     * This method will print who won the game.
     *
     * @param player    The name of the player who won the game.
     */
    public static void printWinner(String player) {
        System.out.println("What a twist! Amazing card skills!! " + player +
                ", you've won!");
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
        System.out.println("\nWhat's this, the end? Say it isn't so!");

        do {
            System.out.print("Wanna play again? Come on, I dare ya! (No to " +
                    "exit, if you must): ");
            input = keybd.nextLine().toLowerCase();
        } while (input.length() < 1 || repeatAnswers(input) == null);
        answer = input.charAt(0);
        return answer;
    }

    /**
     * This method will check the answer entered by the user to determine if
     * the user wants to proceed or not. Only approved answers will be
     * accepted. Given the nature of yes and no, the responses are hardcoded
     * with the most common nomenclatures for them in order to loop the program.
     * If they input no, no is returned, else null
     *
     * @param answer The user's inputted answer in the repeat method.
     * @return The final answer determined based on the approved responses.
     */
    private static String repeatAnswers(String answer) {
        return switch (answer) {
            case "yes", "sure", "yeah", "yep", "okay", "y" -> "yes";
            case "no", "nah", "nope", "n" -> "no";
            default -> null;
        };
    }

    /**
     * A short goodbye message once the game is completed and the user
     * doesn't want to play again
     */
    public static void goodbye() {
        System.out.println("\nWell, I'm sad about your decision, but " +
                "you're entitled to\nyour opinions. Don't be a stranger, it " +
                "gets lonely, okay? \nThanks for playing our Silly Game! See" +
                " ya later!");
    }

    /**
     * The main method will run through the game play as many times as the
     * user(s) wants to. Given how long the game can go for, the turns are
     * not dependent upon user input, but automated instead. The user(s) can
     * repeat the game as many times as they wish.
     *
     * @param args  The String arguments from the command line.
     */
    public static void main(String[] args) {
                int numPlayers;
        final char YES ='y';
        char repeat;

        Scanner keybd = new Scanner(System.in);

        welcome();
        do {
            ArrayList<String> playerNames = new ArrayList<>();
            ArrayList<PlayerQueue<Integer>> playerHands;
            GameModel newGame = new GameModel();

            numPlayers = numPlayers(keybd);
            playerNames(keybd, playerNames, numPlayers);
            playerHands = newGame.players(playerNames);
            newGame.createNewDeck();
            newGame.initiateGame();
            newGame.dealCards(playerHands);
            playGame(newGame, playerNames, playerHands);
            repeat = repeatGame(keybd);
        } while (repeat == YES);

        keybd.close();
        goodbye();
    }
}
