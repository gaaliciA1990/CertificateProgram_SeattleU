/**
 * Author: Alicia Garcia
 * Version: 1.0
 * Date: 4/27/2021 20:57
 */


public class LaunchMergeSort {
    /**
     *
     * @param args
     */
    public static void main(String args[]) {
        int test1[] = {};
        int test2[] = {0,1,2,3};
        int test3[] = {0,1,2,3,4};
        int test4[] = {3,1,4,1,5,9,2,6,5};
        int test5[] = {9,8,7,6,5,4,3,2,1,0};

        System.out.println("Given Array 1");
        printArray(test1);

        mergeTest(test1);

        System.out.println("\nGiven Array 2");
        printArray(test2);

        mergeTest(test2);

        System.out.println("\nGiven Array 3");
        printArray(test3);

        mergeTest(test3);

        System.out.println("\nGiven Array 4");
        printArray(test4);

        mergeTest(test4);

        System.out.println("\nGiven Array 5");
        printArray(test5);

        mergeTest(test5);

    }

    public static void mergeTest(int[] test) {
        MergeSort mergeArray = new MergeSort();
        mergeArray.mergeSort(test, test.length);

        System.out.println("Sorted array");
        printArray(test);
    }

    /**
     * A helper printing method to print array of size n
     * @param arr
     */
    static void printArray(int arr[]) {
        for (int i = 0; i < arr.length; ++i) {
            System.out.print(arr[i] + " ");
        }
        System.out.println();
    }
}
