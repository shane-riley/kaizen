import java.util.Scanner;

/**
 * Copied from text
 * Class: CIT 130
 * Date: 06/29/2020
 */

public class GenericPairDemo
{
    public static void main(String[] args)
    {
        Pair<String> secretPair = new Pair<>("Happy", "Day");
        Scanner keyboard = new Scanner(System.in);
        System.out.println("Enter two words:");
        String word1 = keyboard.next();
        String word2 = keyboard.next();
        Pair<String> inputPair = new Pair<>(word1, word2);
        if (inputPair.equals(secretPair))
        {
            System.out.println("Correct!");
        }
        else
        {
            System.out.println("Incorrect.");
            System.out.println("Answer was:");
            System.out.println(secretPair);
        }
    }
}
