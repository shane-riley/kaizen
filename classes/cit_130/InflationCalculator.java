import java.util.Scanner;
import java.text.DecimalFormat;

/**
 * A simple inflation calculator
 * Class: CIT 130
 * Date: 05/24/2020
 * @author Shane Riley
 * @version 1.0
 */

public class InflationCalculator
{
    public static void main(String[] args)
    {
        double initial_cost;
        double percent_inflation;
        double inflated_cost;
        int num_years;
        Scanner scanner = new Scanner(System.in);

        System.out.println("Welcome to the inflation calculator!");

//        Gather inputs

        System.out.print("Enter the current cost of the item: ");
        initial_cost = scanner.nextDouble();

        System.out.println();

        System.out.println("Enter the expected inflation rate per year");
        System.out.print("(Enter as a percentage and do not include the percent sign): ");
        percent_inflation = scanner.nextDouble();

        System.out.print("Enter the whole number of years in the future to project cost: ");
        num_years = scanner.nextInt();

//        Calculate inflated cost

        inflated_cost = initial_cost;
        for (int year = 0; year < num_years; year++)
            inflated_cost *= 1 + (percent_inflation / 100.0);

//        Display output

//        Using printf
//        System.out.printf("At %.2f%% inflation per year, the cost in %d year(s) will be $%,.2f.",
//                percent_inflation, num_years, inflated_cost);

//        Using DecimalFormat
        DecimalFormat df1 = new DecimalFormat("#,##0.00'%'");
        DecimalFormat df2 = new DecimalFormat("#");
        DecimalFormat df3 = new DecimalFormat("$#,##0.00");
        System.out.println("At " + df1.format(percent_inflation) + " inflation per year, the cost in "
            + df2.format(num_years) + " year(s) will be " + df3.format(inflated_cost) + ".");

//        Come back to this later


    }
}
