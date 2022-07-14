import java.util.Scanner;

/**
 * A class for testing Fraction
 * Class: CIT 130
 * Date: 06/02/2020
 * @author Shane Riley
 * @version 1.0
 */

public class FractionHarness
{
    public static void main(String[] args)
    {
        char again;
        Scanner keyboard = new Scanner(System.in);

//        Set up target fraction
        System.out.print("Enter the numerator and denominator for the target fraction, separated by a space: ");
        int targetNum = keyboard.nextInt();
        int targetDen = keyboard.nextInt();
        Fraction targetFraction = new Fraction(targetNum, targetDen);

//        Run a test and prompt whether to continue
        do
        {
//            Run a test
            System.out.println();
            System.out.println("Target Fraction: " + targetFraction.toString());
            System.out.println("Float value is approximately equal to: " + targetFraction.toFloat());
            System.out.println();

            System.out.print("Enter the numerator and denominator for the test fraction, separated by a space: ");
            int testNum = keyboard.nextInt();
            int testDen = keyboard.nextInt();
            Fraction testFraction = new Fraction(testNum, testDen);

            System.out.println();
            System.out.println("Test Fraction: " + testFraction.toString());
            System.out.println("Float value is approximately equal to: " + testFraction.toFloat());
            System.out.println("Equal to Target: " + testFraction.equals(targetFraction));
            System.out.println();

//            Prompt whether to continue
            do
            {
                System.out.print("Would you like to continue (Y/N)? ");
                again = keyboard.next().charAt(0);
            } while (Character.toUpperCase(again) != 'Y' && Character.toUpperCase(again) != 'N');

        } while (Character.toUpperCase(again) == 'Y');

        System.out.println("Process completed.");
    }
}
