/**
 * A class implementation of QuickSort, featuring modular partitioning and adjustable min size
 * 
 * @author Shane Riley
 * @version 1.0
 * @since 4/11/2021
 */

public class QuickSort<T extends Comparable<? super T>>  implements Sorter<T> {

    private static final int DEFAULT_MIN_SIZE = 5;

    // Instance variables
    private Partitionable<T> partitioner;
    private int minSize;

    // Constructor
    public QuickSort(Partitionable<T> p) {
        this.partitioner = p;
        this.setMin(DEFAULT_MIN_SIZE);
    }

    // Set min
    public void setMin(int newMin) {
        this.minSize = newMin;
    }

    // Quicksort
    public void sort(T[] a, int length) {
        this.recSort(a, 0, length - 1);
    }

    // Inner Quicksort (offers starting pointer)
    private void recSort(T[] a, int first, int last) {

        // Check for min size
        if ((last - first + 1) < this.minSize) {
            this.insertionSort(a, first, last);
        } else {

            // Partition
            int pi = partitioner.partition(a, first, last);

            // Sort left and right sides
            this.recSort(a, first, pi-1);
            this.recSort(a, pi+1, last);
        }
    }

    // Inner insertion sort
    private void insertionSort(T[] a, int first, int last) {

        int currentIndex;

        for (currentIndex = first + 1; currentIndex <= last; currentIndex++) {
            T nextElement = a[currentIndex];
            this.insertInOrder(nextElement, a, first, currentIndex - 1);
        }
    }

    // Insertion sort helper
    private void insertInOrder(T element, T[] a, int first, int last) {
        int index;
        for (index = last; (index >= first) && (element.compareTo(a[index]) < 0); index--) {
            a[index + 1] = a[index];
        }

        a[index + 1] = element;
    }

    
}
