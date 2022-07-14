/**
 * Copied from text
 * Class: CIT 130
 * Date: 06/15/2020
 */

public class MergeSortDemo
{
    public static void main(String[] args)
    {
        double[]b = {7.7, 5.5, 11, 3, 16, 4.4, 20, 14, 13, 42};

        System.out.println("Array contents before sorting:");
        for (double i : b)
            System.out.print(i + " ");
        System.out.println();

        MergeSort.sort(b, 0, b.length-1);
        System.out.println("Sorted array values:");
        for (double i : b)
            System.out.print(i + " ");
        System.out.println();
    }
}
