import java.util.Scanner;
/**
 * Copied from text
 * Class: CIT 130
 * Date: 05/29/2020
 */

public class StringProcessor
{
    public static void main (String[] args)
    {
        System.out.println("Enter a one line sentence:");
        Scanner keyboard = new Scanner(System.in);
        String sentence = keyboard.nextLine();

        sentence = sentence.toLowerCase(); // strings are immutable so must be reassigned with the new value
        char firstCharacter = sentence.charAt(0);
        sentence = Character.toUpperCase(firstCharacter)
                + sentence.substring(1); // add capital letter to rest of string

        System.out.println("The revised sentence is:");
        System.out.println(sentence);
    }
}
