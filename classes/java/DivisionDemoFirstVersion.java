import java.util.Scanner;

/**
 * Copied from text
 * Class: CIT 130
 * Date: 06/15/2020
 */

public class DivisionDemoFirstVersion
{
    public static void main(String[] args)
    {
        try {
            Scanner keyboard = new Scanner(System.in);
            System.out.println("Enter numerator:");
            int numerator = keyboard.nextInt();
            System.out.println("Enter denominator:");
            int denominator = keyboard.nextInt();

            if (denominator == 0)
                throw new DivisionByZeroException();

            double quotient = numerator / (double) denominator;
            System.out.println(numerator + "/" + denominator + " = " + quotient);
        }
        catch (DivisionByZeroException e)
        {
            System.out.println(e.getMessage());
            secondChance();
        }
        System.out.println("End of program");
    }

    public static void secondChance()
    {
        Scanner keyboard = new Scanner(System.in);
        System.out.println("Enter numerator:");
        int numerator = keyboard.nextInt();
        System.out.println("Enter denominator:");
        int denominator = keyboard.nextInt();

        if (denominator == 0) {
            System.out.println("I cannot do that! Aborting.");
            System.exit(0);
        }

        double quotient = numerator / (double) denominator;
        System.out.println(numerator + "/" + denominator + " = " + quotient);
    }
}
