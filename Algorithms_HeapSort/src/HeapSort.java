/**
 * Author: Alicia Garcia
 * Version: 1.0
 * Date: 5/13/2021 12:27
 */


public class HeapSort {
    int heapArray[];

    /**
     * main method to do the Heap Sort
     *
     * @param arr Array to be sorted
     */
    public void sort(int arr[]) {
        this.heapArray = arr;
        int size = heapArray.length;

        buildHeap(heapArray);
        // One by one extract an element from heap
        //and get the sorted array
        for (int i = size - 1; i >= 0; i--) {
            // Move top root element to end element
            swap(0, i);

            // call heapify on the reduced heap
            heapify(arr, i, 0);
        }
    }

    /**
     * Heapify a subtree rooted at node i which is an index in arr[].
     * @param arr   Array to heapify
     * @param size  Size of the array
     * @param i     Node of subtree root within the array
     */
    void heapify(int arr[], int size, int i) {
        int largest = i;  // Initialize largest as root
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        // If left child is larger than root
        if (left < size && arr[left] > arr[largest])
            largest = left;

        // If right child is larger than largest so far
        if (right < size && arr[right] > arr[largest])
            largest = right;

        // If largest is not root
        if (largest != i) {
            swap(i, largest);
            // Recursively heapify the sub-tree
            heapify(arr, size, largest);
        }
    }

    /**
     * Building the heap by rearranging the array. Then converting the array arr to a heap
     * @param arr   Array to convert to a heap
     */
    public void buildHeap(int arr[]) {
        int size = arr.length;
        // Check all root nodes 1x1 and call heapify function if they don't
        // satisfy heap property
        for (int i = arr.length / 2 - 1; i >= 0; i--) {
            heapify(arr, size, i);
        }
    }
    /**
     * Helper method to move the current root to the end, swapping values
     * @param i index of root
     * @param j index to swap with
     */
    private void swap(int i, int j) {
        int temp = heapArray[i];
        heapArray[i] = heapArray[j];
        heapArray[j] = temp;
    }
}
