import java.util.Scanner;
/**
 * Copied from text
 * Class: CIT 130
 * Date: 06/15/2020
 */

public class DanceLesson
{
    public static void main(String[] args)
    {
        Scanner keyboard = new Scanner(System.in);

        System.out.println("Enter number of male dancers:");
        int men = keyboard.nextInt();

        System.out.println("Enter number of female dancers:");
        int women = keyboard.nextInt();

        try
        {
            if (men <= 0 && women <= 0)
                throw new Exception("Lesson is canceled. No students.");
            else if (men <= 0)
                throw new Exception("Lesson is canceled. No men.");
            else if (women <= 0)
                throw new Exception("Lesson is canceled. No women.");

            if (women >= men)
                System.out.println("Each man must dance with"  +
                        women/(double)men + " women.");
            else
                System.out.println("Each woman must dance with " +
                        men/(double)women + " men.");
        }
        catch(Exception e)
        {
            String message = e.getMessage();
            System.out.println(message);
            System.exit(0);
        }
        System.out.println("Begin the lesson.");
    }
}
