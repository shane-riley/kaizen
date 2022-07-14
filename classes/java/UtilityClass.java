/**
 * Copied from text
 * Class: CIT 130
 * Date: 05/29/2020
 */

public class UtilityClass {

    public static int max(int... arg)
    {
        if (arg.length == 0) {
            System.out.println("Fatal Error.");
            System.exit(0);
        }

        int largest = arg[0];
        for (int i = 1; i < arg.length; i++)
            if (arg[i] > largest)
                largest = arg[i];

        return largest;
    }
}
