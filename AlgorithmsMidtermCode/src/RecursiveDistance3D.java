import java.util.Arrays;

/**
 * Author: Alicia Garcia
 * Version: 1.0
 * Date: 5/1/2021 22:39
 */


public class RecursiveDistance3D {
    public static void main(String[] args) {
        int[] testA1 = {0, 0, 0};
        int[] testA2 = {0, 0, 0};
        printDistance(testA1, testA2);

        int[] testB1 = {1, 2, 3};
        int[] testB2 = {3, 2, 1};
        printDistance(testB1, testB2);

        int[] testC1 = {1, 2, 3, 4, 5};
        int[] testC2 = {1, 1, 1, 1, 0};
        printDistance(testC1, testC2);

        int[] testD1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int[] testD2 = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        printDistance(testD1, testD2);

        int[] testE1 = {5, 4, 9, 6, 2};
        int[] testE2 = {1,5,3,7};
        printDistance(testE1, testE2);
    }

    public static void printDistance(int[] arr1, int[] arr2) {
        if (arr1.length == 0 | arr2.length == 0) {
            throw new IllegalArgumentException("ERROR: Empty array found, invalid request.");
        }
        if (arr1.length != arr2.length) {
            throw new IllegalArgumentException("ERROR: Unequal array sizes found, invalid request.");
        }

        System.out.println("Testing arrays " + Arrays.toString(arr1) + " and " + Arrays.toString(arr2));
        System.out.println(squareRoot(arr1, arr2, arr1.length));
        System.out.println();
    }

    public static float squareRoot(int p1[], int p2[], int numDimensions) {
        float total = distance(p1, p2, numDimensions);

        return (float) Math.sqrt(total);
    }

    public static float distance(int p1[], int p2[], int numDimensions) {
        double sum = 0;

        if (numDimensions == 0) {
            return 0;
        }
        sum += Math.pow((p2[numDimensions - 1] - p1[numDimensions - 1]), 2) + distance(p1, p2, numDimensions -1);

        return (float) sum;
    }
}
