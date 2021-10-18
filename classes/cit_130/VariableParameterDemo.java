import java.util.Scanner;

/**
 * Copied from text
 * Class: CIT 130
 * Date: 05/29/2020
 */

public class VariableParameterDemo {

    public static void main(String[] args)
    {
        System.out.println("Enter three scores:");
        Scanner keyboard = new Scanner(System.in);
        int score1 = keyboard.nextInt();
        int score2 = keyboard.nextInt();
        int score3 = keyboard.nextInt();

        int highScore = UtilityClass.max(score1, score2, score3);
        System.out.println("The high score is " + highScore);
    }
}
