import java.util.Scanner;

/**
 * Copied from text
 * Class: CIT 130
 * Date: 06/15/2020
 */

public class DivisionDemoSecondVersion
{
    public static void main(String[] args)
    {
        try {
            Scanner keyboard = new Scanner(System.in);
            System.out.println("Enter numerator:");
            int numerator = keyboard.nextInt();
            System.out.println("Enter denominator:");
            int denominator = keyboard.nextInt();

            double quotient = safeDivide(numerator, denominator);

            System.out.println(numerator + "/" + denominator + " = " + quotient);
        }
        catch (DivisionByZeroException e)
        {
            System.out.println(e.getMessage());
            secondChance();
        }
        System.out.println("End of program");
    }

    public static double safeDivide(int num, int den) throws DivisionByZeroException
    {
        if (den==0)
            throw new DivisionByZeroException();
        return (num / (double) den);
    }

    public static void secondChance()
    {
        try {
            Scanner keyboard = new Scanner(System.in);
            System.out.println("Enter numerator:");
            int numerator = keyboard.nextInt();
            System.out.println("Enter denominator:");
            int denominator = keyboard.nextInt();
            double quotient = safeDivide(numerator, denominator);
            System.out.println(numerator + "/" + denominator + " = " + quotient);
        }
        catch (DivisionByZeroException e)
        {
            System.out.println("I cannot do that! Aborting.");
            System.exit(0);
        }
    }
}
