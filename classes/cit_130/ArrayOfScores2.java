import java.util.Scanner;

/**
 * Copied from text
 * Class: CIT 130
 * Date: 05/29/2020
 */

public class ArrayOfScores2
{
    public static void main(String[] args)
    {
        Scanner keyboard = new Scanner(System.in);
        double[] score = new double[5];
        int index;
        double max;

        System.out.println("Enter " + score.length + " scores:");
        score[0] = keyboard.nextDouble();
        max = score[0];
        for (index = 1; index < score.length; index++) {
            score[index] = keyboard.nextDouble();
            if (score[index] > max)
                max = score[index];
        }

        System.out.println("The highest score is " + max);
        System.out.println("The scores are:");
        for (index = 0; index < score.length; index++)
            System.out.println(score[index] + " differs from max by " + (max - score[index]));
    }
}
