import java.util.Scanner;
/**
 * Copied from text
 * Class: CIT 130
 * Date: 05/29/2020
 */

public class DateSecondTry
{
    private String month;
    private int day;
    private int year; // all instance variables are set as "private" to prevent people from modifying/reading them directly

    public void writeOutput()
    {
        System.out.println(month + " " + day + " " + year);
    }

    public void readInput()
    {
        Scanner keyboard = new Scanner(System.in);
        System.out.println("Enter month, day, and year.");
        System.out.println("Do not use a comma.");
        month = keyboard.next();
        day = keyboard.nextInt();
        year = keyboard.nextInt();
    }

//    Accessors
    public int getDay()
    {
        return day;
    }

    public int getYear()
    {
        return year;
    }

    public int getMonth()
    {
        String[] months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        int size = months.length;
        for (int i = 0; i < size; i++)
        {
            if (months[i].equalsIgnoreCase(month))
                return 1 + i;
        }
        System.out.println("Fatal error");
        System.exit(0);
        return -1;
    }
}
