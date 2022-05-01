import java.util.Scanner;

/**
 * Copied from text
 * Class: CIT 130
 * Date: 07/01/2020
 */

public class BinarySearchTreeDemo
{
    public static void main(String[] args)
    {
        Scanner keyboard = new Scanner(System.in);
        IntTree tree = new IntTree();

        System.out.println("enter a list of nonnegative integers.");
        System.out.println("Place a negative integer at the end.");
        int next = keyboard.nextInt();
        while (next >= 0)
        {
            tree.add(next);
            next = keyboard.nextInt();
        }

        System.out.println("In sorted order:");
        tree.showElements();
    }
}
