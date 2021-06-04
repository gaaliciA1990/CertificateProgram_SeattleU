import java.util.Arrays;

/**
 * Author: Alicia Garcia
 * Version: 1.0
 * Date: 5/13/2021 12:27
 */


public class Sort {
    public static void main(String[] args) {
        // This test case models a max heap
        int test1[] = {14,10,13,6,2,9,5};
        // This test case is already sorted
        int test2[] = {3,7,9,10,11,16,21};
        // This test case has a lot of duplicates
        int test3[] = {0,0,0,0,5,1,2,0,0,0};
        // Always test an empty array
        int test4[] = {};
        // This test case has negative numbers and positive numbers
        int test5[] = {-1,-6,-8,2,8,-9};
        // This test case has the same number at the ends.
        int test6[] = {1,9,3,4,2,1 };

        heapSorter(test1);
        heapSorter(test2);
        heapSorter(test3);
        heapSorter(test4);
        heapSorter(test5);
        heapSorter(test6);
    }

    public static void heapSorter(int test[]) {
        //print unsorted array using Arrays.toString()
        System.out.print("Unsorted array: ");
        System.out.println(Arrays.toString(test));

        HeapSort heap = new HeapSort();
        heap.sort(test);

        System.out.print("Sorted array: ");
        //print sorted array using Arrays.toString()
        System.out.println(Arrays.toString(test));
        System.out.println();
    }
}
