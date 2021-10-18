/**
 * A class implementation of partitioning using a median-of-three pivot assignment
 * 
 * @author Shane Riley
 * @version 1.0
 * @since 4/11/2021
 */

public class MedOfThree<T extends Comparable<? super T>> implements Partitionable<T> {

    // Partitioning method
    // a is the array
    // first is the first logical index
    // last is the last logical index
    // return is the index of the pivot post-partition
    public int partition(T[] a, int first, int last) {
        
        // Put the highest of three at the end, with the pivot (median of three) before it
        int mid = (first + last)/2;
        tripleOrder(a, first, mid, last);
        swap(a, mid, last - 1);

        // Make the pointers
        int li = first + 1;  // We know a[first] is fine
        int ri = last - 2;   // We know the last two are fine
        int pi = last - 1;
        T pivot = a[pi];

        boolean done = false;
        while (!done)
        {
            // Skip until first out-of-place on left
            while (a[li].compareTo(pivot) < 0) li++;

            // Skip until first out-of-place on right
            while (a[ri].compareTo(pivot) > 0 
                    && ri > first) ri--;

            // Now we need swaps
            if (li < ri)
            {
                swap(a, li, ri);
                li++;
                ri--;
            }
            else
                done = true;       
        }

        // Put the pivot in
        swap(a, pi, li);
        pi = li;

        return pi;
    }

    // Swap in place
    private static void swap(Object[] a, int i, int j)
    {
        // Do the swap
        Object temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }

    // Ordered swap (ascending order)
    private static <T extends Comparable<? super T>>
        void order(T[] a, int i, int j) {
        if (a[i].compareTo(a[j]) > 0) swap(a, i, j);
    }

    // Triple order
    private static <T extends Comparable<? super T>>
        void tripleOrder(T[] a, int i, int j, int k) {
            order(a, i, j);
            order(a, j, k);
            order(a, i, j);
        }
}
