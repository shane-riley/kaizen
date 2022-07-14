/**
 * Copied from text
 * Class: CIT 130
 * Date: 06/15/2020
 */

public class BinarySearch
{
    public static int search(int[] a, int first, int last, int key)
    {
        int result = 0;

        if (first > last)
            result = -1;
        else
        {
            int mid = (first + last)/2;

            if (key == a[mid])
                result = mid;
            else if (key < a[mid])
                result = search(a, first, mid - 1, key);
            else if (key > a[mid])
                result = search(a, mid + 1, last, key);
        }
        return result;
    }

    public static void main(String[] args)
    {
        int[] testArray = {1, 2, 3, 4, 5, 6, 7, 8};
        System.out.println("Value of 5 at location "
            + search(testArray, 0, testArray.length, 5));
    }
}
