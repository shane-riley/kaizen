import java.util.Scanner;
import java.util.InputMismatchException;

/**
 * Copied from text
 * Class: CIT 130
 * Date: 06/15/2020
 */

public class InputMismatchExceptionDemo
{
    public static void main(String[] args)
    {
        Scanner keyboard = new Scanner(System.in);
        int number = 0; //to keep compiler happy
        boolean done = false;

        while(!done)
        {
            try
            {
                System.out.println("Enter a whole number:");
                number = keyboard.nextInt();
                done = true;
            }
            catch(InputMismatchException e)
            {
                keyboard.nextLine(); // clears scanner
                System.out.println("Input error.");
                System.out.println("Try again.");
            }
        }
        System.out.println("You entered " + number);
    }
}
