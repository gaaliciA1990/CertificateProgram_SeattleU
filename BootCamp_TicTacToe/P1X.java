package agarcia3_p1;

import java.util.Scanner;

/**
 * This program will run through a game of tic-tac-toe as many times as the
 * users want. Two players will alternate between entering their symbol (X or
 * O) in the 3x3 board. After each round, a winner is declared, if any and
 * the statistics from each game played is displayed.
 */
public class P1X {

    /**
     * Prints the welcome message, with a short description of the how the
     * program will run.
     */
    public static void welcome() {
        System.out.println("\nWelcome to Tic-Tac-Toe! In this game, there " +
                "are\ntwo players, one for X and one for O. You and your\n" +
                "opponent will alternate indicating where you want to place\n" +
                "your symbol on the board. The first one to fill a row,\n" +
                "column, or diagonal wins. If no one gets either filled,\n" +
                "the game ends in a draw. You get to decide how big the\n" +
                "board will be.\nX's will go first.\n");
    }

    /**
     * This method asks the user for the size of the tic-tac-toe board they'd
     * like to play on. Only odd numbers are accepted, up to 25.
     * @param keybd Scanner object for entering the user input
     * @return the size of the board
     */
    public static int getBoardSize(Scanner keybd) {
         // variables for the board size and checking if the number is odd
        int size, odd;

       do {
           do {
               System.out.print("Enter the size of the board you'd like to " +
                       "play on. Only odd numbers are accepted (up to 25): ");
               size = keybd.nextInt();
               keybd.nextLine();
               odd = size % 2;
               if ( odd == 0) {
                   System.out.println("Invalid number, please enter an odd " +
                           "number.");
               }
           } while (odd == 0);
       }  while (size < 1 || size > 25);
       return size;
    }

    /**
     * Asks the player to enter the row they would like to place their symbol.
     * @param keybd Scanner object for entering the row
     * @param player Current player in the turn
     * @return the row number entered by the player
     */
    public static int getPlayerXLocation(Scanner keybd, char player) {
        int row;

        System.out.println("\n" + player + " it's your turn.");
        System.out.print("What row would you like? ");
        row = keybd.nextInt();
        keybd.nextLine();
        return row;
    }

    /**
     * Asks the player to enter the row they would like to place their symbol.
     * @param keybd Scanner object for entering the column
     * @return the column number entered by the player
     */
    public static int getPlayerYLocation(Scanner keybd) {
        int col;

        System.out.print("What column would you like? ");
        col = keybd.nextInt();
        keybd.nextLine();
        System.out.println(); // Add new line for spacing
        return col;
    }

    /**
     * Asks the user if they'd like to repeat the game
     * @param keybd Scanner object for enter the response
     * @return the char variable from the player response
     */
    public static char repeatGame(Scanner keybd) {
        // input string for repeat question to compare values entered
        String input;
        do {
            System.out.print("\nWant to play again (Y/N)? ");
            input = keybd.nextLine().toLowerCase();
        } while (input.length() < 1);
        return input.charAt(0);
    }

    /**
     * Prints the goodbye message at the end of the game
     */
    public static void goodbye() {
        System.out.println("\nThank you for playing Tic-Tac-Toe!");
    }

    /**
     * The main method will create an instance of the tic-tac-toe game and
     * run through the gameplay with the users. Once the game is completed,
     * the game stats will be displayed and the user asked if they would like
     * to play again
     * @param args  String argument for command line input
     */
    public static void main(String[] args) {
        char currentPlayer;
        boolean winner;
        int size;
        int xLocation, yLocation;   // grid coordinates for player moves
        char repeat;

        welcome();
        Scanner keybd = new Scanner(System.in);
        size = getBoardSize(keybd);
        TicTacToeX game = new TicTacToeX(size);

        do {
            game.setBoard();
            boolean continueGame = false;
            do {
                game.printBoard();
                currentPlayer = game.getCurrentPlayer();
                boolean turnCompleted = false;
                // Play the game
                do {
                    xLocation = getPlayerXLocation(keybd, currentPlayer);
                    yLocation = getPlayerYLocation(keybd);
                    turnCompleted = game.populateBoard(xLocation, yLocation);
                    if (!turnCompleted) {
                        System.out.println("Bad location, try again..\n");
                        game.printBoard();
                    }
                } while (!turnCompleted);
                // check if the game should continue
                continueGame =
                        !game.isBoardFull() && !game.checkWinner();
                // Display the winner, if the board is full or a winner found
                if (!continueGame) {
                    game.printWinner();
                }
                // proceed with the game play and alternate the player if
                // above is not met
                else {
                    game.changePlayer();
                }
            } while (continueGame);

            // print the board after the winner's move
            game.printBoard();
            game.gameStatistics();  // show the total wins and ties in the game
            repeat = repeatGame(keybd);
        } while (repeat == 'y');

        keybd.close();
        goodbye();
    }
}