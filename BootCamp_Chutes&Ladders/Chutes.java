import java.util.Scanner; 
import java.util.ArrayList;
import java.util.Random;
import java.io.*;

/**
* This class demonstrates the board game Chutes and Ladders. 2 to 6 players can
* be entered to play the game. Each name of the player is entered and stored. 
* Each player "spins" to determine how many spaces they move during their turn.
* If they land on a ladder space, they move extra spaces, and conversely, if
* they land on a chutes space, they move back XX number of spaces. Once a
* player has reached the 100th space, the game ends and a winner is announced.
* The user(s) can play as many times as they wish. 
*
* @author Alicia Garcia
* @version 1.0
*/
public class Chutes {
   
   /**
   * The welcome message at the beginning of the game
   */
   public static void welcomeMesssage() {
      System.out.println("\nWelcome to Chutes & Ladders! You must land on 100"
            + " (without going past) to win!\nYou will play against" +
            " the computer.");
   }
   
   /**
   * This method will ask the user how many players will be participating
   * in the game. If the user enters a number less than 2 or greater than
   * 6, the question will be asked again.
   *
   * @param keybd passes the Scanner object to accept user inputs
   * @return   returns the number of players
   */
   public static int getPlayers(Scanner keybd){
      int playerNum; 
      
      do {
         System.out.print("How many players will be playing (between 2-6)? ");
         playerNum = keybd.nextInt();
         keybd.nextLine();    // clear new line for names
      } while (playerNum < 2 || playerNum > 6);
      
      return playerNum;
   }
   
   /**
   * This method will ask for the names of the players and return them in 
   * a string array list.
   *
   * @param keybd passes the Scanner object to accept user inputs
   * @param playerNum   the number of players participating in the game
   * @returns returns the ArrayList of names entered by the user
   */
   public static ArrayList<String> getNames(Scanner keybd, int playerNum) {
      ArrayList<String> playerList = new ArrayList<>();
      
      for (int i = 0; i < playerNum; i++) {
         System.out.printf("Enter player %d's name: ", (i + 1));
         playerList.add(keybd.nextLine());
      }
      System.out.println(); // Adding newline for formatting
      return playerList;
   }
   
   /**
   * This method will open the file and read the contents to populate an 
   * array with the values for the ladders and chutes in the board game
   *
   * @param arrayBoard  the board game
   * @param fileName    the file containing values for the array positions
   * @returns returns the board game array created from the file
   * @throws   if the file doesn't exist, the program will end.
   */
   public static int[] getTableData(int[] arrayBoard, String fileName) throws
                              IOException {
      int fileIndex; // The index of the board game to check against the file
      int fileValue; // The value to be filled in the board game array
      
      File file = new File(fileName);
      Scanner inFile = new Scanner(file);
      
      while (inFile.hasNext()) {
         fileIndex = inFile.nextInt();
         fileValue = inFile.nextInt();
         arrayBoard[fileIndex] = fileValue;
      }
      return arrayBoard;
   }
   
   /**
   * This method will generate the spaces to be moved with a dice roll. 
   *
   * @returns returns the integer from the dice roll
   */
   public static int rollDice() {
      final int DICE = 6;
      int moveSpaces;
      
      Random rand = new Random();
      moveSpaces = rand.nextInt(DICE) + 1;
      
      return moveSpaces;
   }
   
   /**
   * This method will move the player on the board based on the dice roll. If
   * the player lands on a space with a ladder (value greater than 0), they
   * will move extra spaces. If the player lands on a chute (value less than
   * 0), they will move back more spaces. 
   *
   *
   * @param playerRoll  The dice roll of the player
   * @param pos   The players position on the board
   * @param arrayBoard  The game board 
   * @return   returns the players new position after the dice is rolled
   */
   public static int playerMoves(int playerRoll, int pos, int[]arrayBoard){
      int newPos = pos; // New position of the player after the die is rolled
      
      newPos += playerRoll;
      
      // Check if the new position is greater than 100 and return the original
      // position if true.
      if (newPos > arrayBoard.length + 1) {
         System.out.println("Sorry, no player can go over 100!");
         return pos;
      }      
      // Check if the value at the position is greater than 0 and add to the
      // index if true. 
      else if (arrayBoard[newPos] > 0) {
         System.out.println("Congrats, that is a ladder! You get to climb " + 
                  arrayBoard[newPos] + " spaces!");
         newPos += arrayBoard[newPos];
         return newPos;
      }
      // Check if the value at the position is less than 0 and add to the
      // index if true. This will move the player back, as the value's negative
      else if (arrayBoard[newPos] < 0) {
         System.out.println("Bummer, that is a chute! You are sent back " + 
                  -(arrayBoard[newPos]) + " spaces.");
         newPos += arrayBoard[newPos];
         return newPos;
      }
      // return the new position with no modifications
      else {
         return newPos;
      }
   }
   
   /**
   * This method will cycle through the players and run playerMoves method for
   * each player entered. Once the players position has hit 100, the winner is 
   * declared.
   *
   * @param playerList  the list of players in the game
   * @param arrayBoard  the game board 
   * @returns  returns the winner of the game
   */
   public static String playerTurns(ArrayList<String> playerList, int[]arrayBoard){
      String playerName;
      int[] playerPos;   // Holds the position of player with each turn
      int diceRoll;
      boolean winnerFound = false;
      
      // initialize the play position to 0 for each player.
      playerPos = new int[playerList.size()];

      while (winnerFound == false) {
         for (int i = 0; i < playerList.size(); i++) {
            playerName = playerList.get(i);
            System.out.printf("\n%s, it's your turn. You are currently at " 
                        + "space %d.\n", playerList.get(i), playerPos[i]); 
            diceRoll = rollDice();
            System.out.println("The spin was: " + diceRoll);
            playerPos[i] = playerMoves(diceRoll, playerPos[i], arrayBoard);
            System.out.println("You are now at space " + playerPos[i] + ".");
            System.out.println();   //Adding new line for formatting
            // Check if the player's position is 100 (size of game board) and 
            // stop executing the game play
            if (playerPos[i] == arrayBoard.length - 1) {
               winnerFound = true; 
               return playerName;
            }
         } 
      }
      // to compile the code as there will never be 0 number of players as I 
      // have a check in getPlayers method
      return null;   
   }
  
   /**
   * This method prints a dividing line for formatting
   */
   public static void printFormattingLine() {
      System.out.println("\n------------------------------\n");
   }
   
   /**
   * This prints the goodbye message when the game is ended
   */
   public static void goodbyeMesssage(){
      System.out.println("Thanks for playing Chutes & Ladders! Bye now!\n");
   }
   
   /**
   * The main method will print the welcomeMessage, ask the user for the number
   * of player and their names. Then the program populates the board game. Then
   * the players play through the game through playerTurns and the winner is
   * returned. The user is asked if they'd like to play again. If not, the 
   * goodbyeMesssage is displayed. 
   *
   * @param args A string array containing the command line arguments.
   * @throws   if the file doesn't exist, the program will end. 
   */
   public static void main(String[] args) throws IOException {
      final String FILENAME = "p3input.txt";
      final int BOARD = 101;  // Size of the game board (100 spaces)
      int playerNumber; // number of players in the game
      ArrayList<String> playerList;
      int[] gameBoard; // The board game array
      String gameWinner;
      char repeat;    // answer from the user if they want to repeat
      
      // Create scanner object
      Scanner keybd = new Scanner(System.in);
      
      // initialize the game board array
      gameBoard = new int[BOARD];
      
      // populate the game Board array
      getTableData(gameBoard, FILENAME);
      
      welcomeMesssage();
            
      do {
         printFormattingLine();
         // Ask for the number of players and their names
         playerNumber = getPlayers(keybd);
         playerList = getNames(keybd, playerNumber);
         printFormattingLine();
           
         // Run through the game
         gameWinner = playerTurns(playerList, gameBoard);
         
         // Print the winner
         System.out.println(gameWinner + ", you have won the game!\n");
         
         // Ask if the user wants to play again
         System.out.print("Do you want to play again? ");
         String input = keybd.nextLine();
         repeat = input.charAt(0);
      } while (repeat == 'Y' || repeat == 'y');

      keybd.close();
      printFormattingLine();
      goodbyeMesssage();
   }
}