/**
 * Author: Alicia Garcia
 * Version: 1.0
 * Date: 4/21/2021 20:30
 */


package KnapsackProblem;

import java.util.ArrayList;

/**
 * This will run the program for determining what combination of items will produce the maximum value.
 */
public class KnapsackLauncher {
    /**
     * Main method initializes our Item data and prints the results and item combination
     *
     * @param args The string argument from the command line
     */
    public static void main(String[] args) {
        ArrayList<Item> itemData = new ArrayList<>();

        int knapsackMaxWt = 10;
        int w1 = 7, w2 = 3, w3 = 4, w4 = 5;
        int v1 = 42, v2 = 12, v3 = 40, v4 = 25;

        itemData.add(new Item(w1, v1));
        itemData.add(new Item(w2, v2));
        itemData.add(new Item(w3, v3));
        itemData.add(new Item(w4, v4));

        Knapsack bag = new Knapsack(knapsackMaxWt);

        int maxValue = bag.sackMaxValue(itemData);

        System.out.println("$" + maxValue);
        System.out.println("The item's weights and values with highest total value:\n" + bag.getMaxItems());
    }
}
