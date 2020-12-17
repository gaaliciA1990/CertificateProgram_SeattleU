package agarcia3_p1;

/**
 * This class will build the empty tic tac toe game board and then populate the
 * board with X's and O's as the players indicate where they would like to
 * place their turn. With each round, the board will be displayed to the users.
 * The winners will be tracked and displayed at the end of the game.
 *
 * @author Alicia Garcia
 * @version 1.0
 */

public class TicTacToeX {
    private char[][] board; // The board game array for tic tac toe
    private char currentPlayer;
    int xWins = 0, oWins = 0, ties = 0; //track the wins per player, or ties

    /**
     * The constructor method initializes the board and sets the
     * currentPlayer to X
     * @param x  The size of the board
     */
    public TicTacToeX(int x) {
        board = new char[x][x];
        currentPlayer = 'X';
    }

    /**
     * The setBoard will create a blank board when called upon
     */
    public char[][] setBoard() {
        for (int row = 0; row < board.length; row++) {
            for (int col = 0; col < board[row].length; col++) {
                board[row][col] = ' ';
            }
        }
        return board;
    }

    /**
     * Prints the board after creation and after each turn
     */
    public void printBoard() {
        System.out.print(" ");  // Add a space before the first row
        for (int row = 0; row < board.length; row++) {
            System.out.printf("%2d  ", row);
        }
        System.out.println();   // print a new line

        for (int row = 0; row < board.length; row++) {
            System.out.print(row + " ");
            for (int col = 0; col < board[row].length; col ++) {
                System.out.print(board[row][col] + " | ");
            }
            System.out.println();   // print a new line
            System.out.print("  ");
            // print the divider for each row based on the array length
            for (int i = 0; i < board[row].length; i++) {
                System.out.print("----");
            }
            System.out.println();   // print a new line
        }
    }

    /**
     * Gets the current player of the game turn a given turn (X or O)
     * @return the curent player in the turn
     */
    public char getCurrentPlayer() {
        return currentPlayer;
    }

    /**
     * Alternates between each player to ensure the board is filled correctly
     */
    public void changePlayer() {
        if (currentPlayer == 'X') {
            currentPlayer = 'O';
        }
        else {
            currentPlayer = 'X';
        }
    }

    /**
     * Place the X or the O for the player in their indicated location. The
     * method will check if the space is empty and return true, else false.
     *
     * @param x The users inputted row coordinate.
     * @param y The users inputted column coordinate.
     * @return whether the space is empty and populates (true) or not (false).
     */
    public boolean populateBoard(int x, int y) {
        if (x >= 0 && x < board.length) {
            if (y >= 0 && y < board.length) {
                if (board[x][y] == ' ') {
                    board[x][y] = currentPlayer;
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * The isBoardFull method will determine if the board is full.
     * @return whether the board is full (true) or not (false)
     */
    public boolean isBoardFull() {
        for( int row = 0; row < board.length; row++) {
            for (int col = 0; col < board[row].length; col++) {
                if (board[row][col] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * The getWinner method will check if a player has won, and if so, returns
     * true.
     * @return the results from the Check winners methods (true or false)
     */
    public boolean checkWinner() {
        return (checkRowsForWin() || checkColsForWin() ||
                checkLeftDiagonalsForWin() || checkRightDiagonalsForWin());
    }

    /**
     * Prints the winner of each game and counts the number of wins each
     * player has and the number of ties from each game.
     */
    public void printWinner() {
        if (checkWinner() == true) {
            System.out.println(currentPlayer + " is the winner!\n");
            if (currentPlayer == 'X') {
                xWins++;
            }
            else {
                oWins++;
            }
        }
        else {
            System.out.println("It's a tie, no winner.\n");
            ties++;
        }
    }

    /**
     * Prints the game wins for X and O and the number ties after each round.
     * This will be a cumulative set of data.
     */
    public void gameStatistics() {
        System.out.printf("X has won %d many games.\n", xWins);
        System.out.printf("O has won %d many games.\n", oWins);
        System.out.printf("There have been %d ties.\n", ties);
    }

    /**
     * The checkRowsForWin method will verify if the rows are all filled with
     * the same symbol.
     * @return true if the rows are all filled with the same symbol, else false
     */
    private boolean checkRowsForWin() {
        for (int row = 0; row < board.length; row++) {
            boolean found = true;
            for (int col = 0; col < board.length; col++) {
                if (board[row][col] != currentPlayer) {
                    found = false;
                }
            }
            if (found) {
                return true;
            }
        }
        return false;
    }

    /**
     * The checkColsForWin method will verify if the columns are filled with
     * the same symbol
     * @return true if the cols are all filled with the same symbol, else false
     */
    private boolean checkColsForWin() {
        for (int col = 0; col < board.length; col++) {
            boolean found = true;
            for (int row = 0; row < board.length; row++) {
                if (board[row][col] != currentPlayer) {
                    found = false;
                }
            }
            if (found) {
                return true;
            }
        }
        return false;
    }

    /**
     * The method will verify if the right diagonals are all filled with the
     * same symbol.
     * @return true if the right diagonals are all filled with the same
     *         symbol, else false
     */
    private boolean checkRightDiagonalsForWin() {
        int col = 0;
        for (int row = 0; row < board.length; row++) {
            if (board[row][col] != currentPlayer) {
                return false;
            }
            else {
                col++;
            }
        }
        return false;
    }

    /**
     * The method will verify if the left diagonals are all filled with the
     * same symbol
     * @return true if the left diagonals are all filled with the same symbol,
     *          else false
     */
    private boolean checkLeftDiagonalsForWin() {
        for (int row = 0; row < board.length; row++) {
            // Find the index of the col and reduce each loop
            int col = board.length - 1 - row;
            if (board[row][col] != currentPlayer) {
                return false;
            }
        }
        return true;
    }
}