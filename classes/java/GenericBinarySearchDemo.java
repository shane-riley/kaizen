/**
 * A Generalized Binary Search Implementation (Testing)
 * Class: CIT 130
 * Date: 06/30/2020
 * @author Shane Riley
 * @version 1.0
 */

public class GenericBinarySearchDemo
{
    public static void main(String[] args)
    {
        Integer[] integerArray = { 1, 3, 15, 27, 46, 58, 72, 99 };
        String[] stringArray = {"Allegheny", "Butler", "Crawford", "Erie", "Fayette", "Westmoreland"};

        Integer[] integerTestArray = { -1, 0, 1, 15, 53, 58, 2, 98, 99};
        String[] stringTestArray = {"Allegheny", "Westmoreland", "Cleveland", "Germany", "Fayette"};

        int index;
        System.out.println("Testing GenericBinarySearch for Integers:");
        System.out.println();

//        Integer Tests
        for (int testInteger : integerTestArray)
        {
            index = GenericBinarySearch.<Integer>search(integerArray, 0, integerArray.length, testInteger);
            if (index == -1)
                System.out.println(testInteger + " was not found in the array!");
            else
                System.out.println(testInteger + " was found at location: " + index);
        }

        System.out.println();

//        String Tests
        for (String testString : stringTestArray)
        {
            index = GenericBinarySearch.<String>search(stringArray, 0, stringArray.length, testString);
            if (index == -1)
                System.out.println(testString + " was not found in the array!");
            else
                System.out.println(testString + " was found at location: " + index);
        }

    }
}
