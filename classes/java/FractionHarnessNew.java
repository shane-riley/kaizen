import java.util.Scanner;

/**
 * A class for testing FractionNew
 * Class: CIT 130
 * Date: 06/15/2020
 * @author Shane Riley
 * @version 1.0
 */

public class FractionHarnessNew
{
    public static void main(String[] args)
    {
        char again;
        Scanner keyboard = new Scanner(System.in);

//        Set up target fraction (include error checking)
        FractionNew targetFraction = null; // for scope
        while(true) {

//            Gather inputs
            System.out.print("Enter the numerator and denominator for the target fraction, separated by a space: ");
            int targetNum = keyboard.nextInt();
            int targetDen = keyboard.nextInt();
            keyboard.nextLine();

//            Attempt construction
            try {
                targetFraction = new FractionNew(targetNum, targetDen);
                break;
            } catch (DenominatorIsZeroException e) {
                System.out.println(e.getMessage());
            }
        }


//        Run a test and prompt whether to continue
        do
        {
//            Display target fraction
            System.out.println();
            System.out.println("Target Fraction: " + targetFraction.toString());
            System.out.println();

//            Set up test fraction (include error checking)
            FractionNew testFraction = null; // for scope
            while (true) {

//                Gather inputs
                System.out.print("Enter the numerator and denominator for the test fraction, separated by a space: ");
                int testNum = keyboard.nextInt();
                int testDen = keyboard.nextInt();

//                Attempt construction
                try {
                    testFraction = new FractionNew(testNum, testDen);
                    break;
                } catch (DenominatorIsZeroException e) {
                    System.out.println(e.getMessage());
                }
            }

//            Display result
            System.out.println();
            System.out.println("Test Fraction: " + testFraction.toString());
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
