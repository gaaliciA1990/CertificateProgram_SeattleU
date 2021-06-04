/**
 * Author: Alicia Garcia
 * Version: 1.0
 * Date: 4/27/2021 20:56
 */


public class MergeSort {
    /**
     * This method sorts the arrays using the merge method
     *
     * @param arr
     * @param size
     */
    void mergeSort(int arr[], int size) {
        if (size < 2) {
            return;
        }

        // Find the middle of arr[]
        int mid = size / 2;

        // Create temp arrays with the size of the subarrays determined above
        int[] tempLeft = new int[mid];
        int[] tempRight = new int[size - mid];

        // Copy data to temp arrays
        for (int i = 0; i < mid; i++) {
            tempLeft[i] = arr[i];
        }
        for (int j = mid; j < size; j++) {
            tempRight[j - mid] = arr[j];
        }

        // Sort first and second halves
        mergeSort(tempLeft, mid);
        mergeSort(tempRight, size - mid);

        // Merge the sorted halves
        merge(arr, tempLeft, tempRight, mid, size - mid);
    }

    /**
     *
     * @param arr
     * @param tempL
     * @param tempR
     * @param left
     * @param right
     */
    void merge(int[] arr, int[] tempL, int[] tempR, int left, int right) {
        // Initial indexes of the temp arrays plus the arr[]
        int i = 0, j = 0, k = 0;

        while (i < left && j < right) {
            if (tempL[i] <= tempR[j]) {
                arr[k++] = tempL[i++];
            } else {
                arr[k++] = tempR[j++];
            }
        }

        /* Copy remaining elements of Left[] if any */
        while (i < left) {
            arr[k++] = tempL[i++];
        }

        /* Copy remaining elements of Right[] if any */
        while (j < right) {
            arr[k++] = tempR[j++];
        }
    }
}
