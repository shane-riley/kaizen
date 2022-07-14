/**
 * A class implementation of MergeSort, featuring adjustable min size
 * 
 * @author Shane Riley
 * @version 1.0
 * @since 4/11/2021
 */

public class MergeSort<T extends Comparable<? super T>>  implements Sorter<T> {

    private static final int DEFAULT_MIN_SIZE = 5;

    // Instance variables
    private int minSize;

    // Constructor
    public MergeSort() {
        this.setMin(DEFAULT_MIN_SIZE);
    }

    // Set min
    public void setMin(int newMin) {
        this.minSize = newMin;
    }

    // Quicksort
    public void sort(T[] a, int length) {
        T[] tempArray = (T[])new Comparable<?>[a.length];
        this.recSort(a, tempArray,0, length - 1);
    }

    // Inner Quicksort (offers starting pointer)
    private void recSort(T[] a, T[] tempArray, int first, int last) {
        // Check for min size
        if ((last - first + 1) < this.minSize) {
            this.insertionSort(a, first, last);
        } else {

            // Get midpoint
            int mid = (first + last)/2;
            recSort(a, tempArray, first, mid);
            recSort(a, tempArray, mid + 1, last);

            // Merge
            if (a[mid].compareTo(a[mid + 1]) > 0) 
                merge(a, tempArray, first, mid, last);
        }
    }

    // merge method
    private void merge(T[] a, T[] tempArray, int first, int mid, int last) {

        // Define the halves
        int bh1 = first;
        int eh1 = mid;
        int bh2 = mid + 1;
        int eh2 = last;

        // Both arrays have elements
        int index = bh1;
        for(; (bh1 <= eh1) && (bh2 <= eh2); index++)
        {
            if (a[bh1].compareTo(a[bh2]) <= 0)
            {
                tempArray[index] = a[bh1];
                bh1++;
            } 
            else
            {  
                tempArray[index] = a[bh2];
                bh2++;
            }
        }

        // Finish left
        for (; bh1 <= eh1; bh1++, index++) {
            tempArray[index] = a[bh1];
        }

        // Finish right
        for (; bh2 <= eh2; bh2++, index++) {
            tempArray[index] = a[bh1];
        }        

        // Copy back
        for (index = first; index <= last; index++) {
            a[index] = tempArray[index];
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
