/**
 * Copied from text
 * Class: CIT 130
 * Date: 06/29/2020
 */

public class ComparableDemo
{
    public static void main(String[] args)
    {
//        Use wrapper class
        Double[] d = new Double[10];
        for (int i = 0; i < d.length; i++)
            d[i] = (double) (d.length - i);

        System.out.println("Before sorting:");
        for (int i = 0; i < d.length; i++)
            System.out.print(d[i].doubleValue() + ", ");
        System.out.println();

        GeneralizedSelectionSort.sort(d, d.length);

        System.out.println("After sorting:");
        for (int i = 0; i < d.length; i++)
            System.out.print(d[i] + ", ");
        System.out.println();

        String[] a = new String[10];
        a[0] = "dog";
        a[1] = "cat";
        a[2] = "cornish game hen";
        int numberUsed = 3;

        System.out.println("Before sorting:");
        for (int i = 0; i < numberUsed; i++)
            System.out.print(a[i] + ", ");
        System.out.println();

        GeneralizedSelectionSort.sort(a, numberUsed);

        System.out.println("After sorting:");
        for (int i = 0; i < numberUsed; i++)
            System.out.print(a[i] + ", ");
        System.out.println();
    }
}
