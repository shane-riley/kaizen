/**
 * Copied from text
 * Class: CIT 130
 * Date: 06/15/2020
 */

public class RecursionDemo1 {

    public static void writeVertical(int num)
    {
        if (num < 10)
            System.out.println(num);
        else
        {
            writeVertical(num / 10);
            System.out.println(num % 10);
        }
    }

    public static void main(String[] args)
    {
        System.out.println("writeVertical(3):");
        writeVertical(3);

        System.out.println("writeVertical(12):");
        writeVertical(12);

        System.out.println("writeVertical(123):");
        writeVertical(123);
    }
}
