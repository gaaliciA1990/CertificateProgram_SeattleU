/**
 * Author: Alicia Garcia
 * Version: 1.0
 * Date: 4/21/2021 21:53
 */


package KnapsackProblem;

/**
 * Item class to easily manage item data points
 */
public class Item {
    // variables holding the values of our Items
    private int weight;
    private int value;

    /**
     * Constructor method to initialize our weight and value for an Items
     *
     * @param w weight
     * @param v value
     */
    Item(int w, int v) {
        weight = w;
        value = v;
    }

    /**
     * Getter for the weight of a given Item
     *
     * @return the item's weight
     */
    public int getWeight() {
        return weight;
    }

    /**
     * Getter for the value of a given Item
     *
     * @return the item's value
     */
    public int getValue() {
        return value;
    }

    /**
     * Overriding the to String method to print the items that produced the highest value cost
     *
     * @return the items in string format
     */
    @Override
    public String toString() {
        return "Item {" +
                "weight = " + weight +
                ", value = " + value +
                '}';
    }
}
