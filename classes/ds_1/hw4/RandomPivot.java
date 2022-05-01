import java.util.Random;

/**
 * A class implementation of partitioning using a random pivot assignment
 * 
 * @author Shane Riley
 * @version 1.0
 * @since 4/11/2021
 */

public class RandomPivot<T extends Comparable<? super T>> implements Partitionable<T> {

    // Partitioning method
    // a is the array
    // first is the first logical index
    // last is the last logical index
    // return is the index of the pivot post-partition
    public int partition(T[] a, int first, int last) {
        
        // Grab random pivot between first and last
        Random rd = new Random();
        int pi = rd.nextInt(last - first) + first;
        T pivot = a[pi];

        // Put the pivot at the end
        swap(a, pi, last);
        pi = last;

        // Make the pointers
        int li = first;
        int ri = last - 1;

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
        Object temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
}
