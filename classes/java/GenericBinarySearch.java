/**
 * A Generalized Binary Search Implementation
 * Class: CIT 130
 * Date: 06/30/2020
 * @author Shane Riley
 * @version 1.0
 */

public class GenericBinarySearch
{

//    Search method
//    Precondition: '/a' must be an ascending sorted array
    public static <T extends Comparable> int search(T[] a, int first, int last, T key)
    {

//        Find midpoint of sub-array
        int middle = (first + last) / 2;

//        Failed search  case
        if (first == last)
            return -1;

//        Use compareTo to determine action
        int comparison = key.compareTo(a[middle]);

        if (comparison == 0)
            return middle;
        else if (comparison > 0)
            return search(a, middle + 1, last, key);
        else
            return search(a, first, middle, key);
    }
}
