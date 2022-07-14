import java.util.ArrayList;
/**
 * A Statistics Class for ArrayLists (Testing)
 * Class: CIT 130
 * Date: 06/30/2020
 * @author Shane Riley
 * @version 1.0
 */

public class MyMathClassDemo
{
    public static void main(String[] args)
    {
        int[] a = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        ArrayList<Integer> intList = new ArrayList<>();
        ArrayList<Double> doubleList = new ArrayList<>();

        for (int value : a)
        {
            intList.add(value);
            doubleList.add((double) value);
        }

        System.out.println("Testing program for standard deviation:");

        System.out.println("0-9 used.");
        System.out.println();

        System.out.println("Average from Integer ArrayList:");
        System.out.println(MyMathClass.average(intList));
        System.out.println("STDEV from Integer ArrayList:");
        System.out.println(MyMathClass.stdev(intList));

        System.out.println("Average from Double ArrayList:");
        System.out.println(MyMathClass.average(doubleList));
        System.out.println("STDEV from Double ArrayList:");
        System.out.println(MyMathClass.stdev(doubleList));


    }
}
