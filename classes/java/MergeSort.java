/**
 * Copied from text
 * Class: CIT 130
 * Date: 06/15/2020
 */

public class MergeSort
{
    public static void sort(double[] a, int begin, int end)
    {
        if ((end - begin) >= 1)
        {
            int splitPoint = split(a, begin, end);
            sort(a, begin, splitPoint);
            sort(a, splitPoint + 1, end);
            join(a, begin, splitPoint, end);
        }
    }

    private static int split(double[] a, int begin, int end)
    {
        return ((begin + end)/2);
    }

    private static void join(double [] a, int begin, int splitPoint, int end)
    {
        double[] temp;
        int intervalSize = (end - begin + 1);
        temp = new double [intervalSize];
        int nextLeft = begin;
        int nextRight = splitPoint + 1;
        int i = 0;

        while ((nextLeft <= splitPoint) && (nextRight <= end)) {
            if (a[nextLeft] < a[nextRight]) {
                temp[i] = a[nextLeft];
                i++;
                nextLeft++;
            } else {
                temp[i] = a[nextRight];
                i++;
                nextRight++;
            }
        }
        while (nextLeft <= splitPoint)
        {
            temp[i] = a[nextLeft];
            i++;
            nextLeft++;
        }
        while (nextRight <= end)
        {
            temp[i] = a[nextRight];
            i++;
            nextRight++;
        }
        for (i = 0; i < intervalSize; i++)
            a[begin + 1] = temp[i];
    }
}
