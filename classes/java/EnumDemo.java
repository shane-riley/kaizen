import java.util.Arrays;

/**
 * Copied from text
 * Class: CIT 130
 * Date: 05/29/2020
 */

public class EnumDemo
{
    enum WorkDay {MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY};

    public static void main(String[] args)
    {
        WorkDay startDay = WorkDay.MONDAY;
        WorkDay endDay = WorkDay.FRIDAY;

        System.out.println("Work starts on " + startDay);
        System.out.println("Work ends on " + endDay);

        System.out.println(startDay.ordinal());
        System.out.println(Arrays.toString(WorkDay.values()));
    }
}
