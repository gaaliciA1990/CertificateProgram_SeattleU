/**
 * Author: Alicia Garcia
 * Version: 1.0
 * Date: 4/21/2021 20:31
 */


package KnapsackProblem;

import java.util.ArrayList;

/**
 * This class will determine what combination of Items will have the highest cost and track the items that result in
 * the highest cost
 */
public class Knapsack {
    // Variable for storing the max weight for the bag and an array list of items that result in highest value
    private final int bagMaxWeight;
    private ArrayList<Item> maxItemOptions = new ArrayList<>();

    /**
     * Constructor that initializes the bagMaxWeight to a given value
     *
     * @param maxWt The total weight a bag knapsack can hold
     */
    Knapsack(int maxWt) {
        bagMaxWeight = maxWt;
    }

    /**
     * In this method, we are comparing the weight of combined items with the max weight the bag can hold. If it's <=
     * to the max bag weight, we begin tracking the total value. If the total values combined are less than that
     * previous combinations, it's not saved.
     *
     * @param itemData Arraylist of Items we have saved
     * @return an Arraylist of Items that hold the max options
     */
    public ArrayList<Item> knapsackSolution(ArrayList<Item> itemData) {
        for (int i = 0; i < itemData.size(); i++) {
            int currentWeight = itemData.get(i).getWeight();
            if (currentWeight > bagMaxWeight) {
                //If the item weight is greater than our max bag weight, we need to skip to the next index
                continue;
            }
            ArrayList<Item> currentItemList = new ArrayList<>();
            currentItemList.add(itemData.get(i));

            for (int j = i + 1; j < itemData.size(); j++) {
                int wt = itemData.get(j).getWeight();
                if (getWeight(currentItemList) + wt > bagMaxWeight) {
                    continue;
                }
                currentItemList.add(itemData.get(j));
                if (getValue(currentItemList) > getValue(maxItemOptions)) {
                    maxItemOptions = currentItemList;
                }
            }
        }
        return maxItemOptions;
    }

    /**
     * This will return the maximum value from the solution above
     *
     * @param itemData Arraylist of Items we have saved
     * @return the final max value
     */
    public int sackMaxValue(ArrayList<Item> itemData) {
        return getValue(knapsackSolution(itemData));
    }

    /**
     * Helper method for comparing the weights of lists
     *
     * @param items Arraylist of Items we have saved
     * @return the weight of the Items in the list
     */
    private int getWeight(ArrayList<Item> items) {
        int weight = 0;
        for (Item item : items) {
            weight += item.getWeight();
        }
        return weight;
    }

    /**
     * Helper method for comparing the values of lists
     *
     * @param items Arraylist of Items we have saved
     * @return the value of the Items in the list
     */
    private int getValue(ArrayList<Item> items) {
        int value = 0;
        for (Item item : items) {
            value += item.getValue();
        }
        return value;
    }

    /**
     * This method will return the elements of the arraylist containing the combination of Items with the highest value
     *
     * @return the combination of Items with the highest value
     */
    public ArrayList<Item> getMaxItems() {
        return maxItemOptions;
    }
}
