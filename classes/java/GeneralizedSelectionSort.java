/**
 * Copied from text
 * Class: CIT 130
 * Date: 06/29/2020
 */

public class GeneralizedSelectionSort
{
    /**
     * Precondition: numberUsed <= a.length;
     *              The first numberUsed indexed variables have values.
     * Action: Sorts a so that a[0], a[1], ... , a[numberUsed - 1] are in
     * increasing order by the compareTo method.
     */
    public static void sort(Comparable[] a, int numberUsed)
    {
        int index, indexOfNextSmallest;
        for (index = 0; index < numberUsed - 1; index++)
        {
//            Place correct value in a[index]
            indexOfNextSmallest = indexOfSmallest(index, a, numberUsed);
            interchange(index, indexOfNextSmallest, a);
//            At this point, a is ordered up until a[index]
        }
    }

    /**
     * Returns the index of the smallest value among
     * a[startIndex], a[startIndex+1], ... a[numberUsed - 1]
     */
    private static int indexOfSmallest(int startIndex, Comparable[] a, int numberUsed)
    {
        Comparable min = a[startIndex];
        int indexOfMin = startIndex;
        int index;
        for (index = startIndex + 1; index < numberUsed; index++)
            if (a[index].compareTo(min) < 0) //if a[index] is less than min
            {
                min = a[index];
                indexOfMin = index;
                //min is smallest of a[startIndex] through a[index]
            }
        return indexOfMin;
    }

    /**
     * Precondition: i and j are legal indices for the array a.
     * Postcondition: Values of a[i] and a[j] have been interchanged.
     */

    private static void interchange(int i, int j, Comparable[] a)
    {
        Comparable temp;
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
}
