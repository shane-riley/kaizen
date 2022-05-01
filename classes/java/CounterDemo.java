import java.util.Scanner;

/**
 * Testing class for CounterModel, CounterController, and CounterView
 * Class: CIT 130
 * Date: 06/22/2020
 * @author Shane Riley
 * @version 1.0
 */

public class CounterDemo
{
    public static void main(String[] args)
    {
//        Start
        Scanner keyboard = new Scanner(System.in);
        System.out.println("This program tests a timer.");

        boolean again;
        char response;
        do
        {
//            Prompt for inputs
            System.out.println("Enter a start number of seconds");
            int start = keyboard.nextInt();
            keyboard.nextLine();
            System.out.println("Enter a end number of seconds");
            int end = keyboard.nextInt();
            keyboard.nextLine();


//            Run CounterController
            System.out.println();
            System.out.println("Invoking CounterController");
            System.out.println();

            CounterController counterControl = new CounterController(start, end);
            counterControl.Start();

            System.out.println();

//            Prompt whether to continue
            do {
                System.out.println("Continue? (y/n)");
                response = Character.toLowerCase(keyboard.next().charAt(0));
                keyboard.nextLine();
            } while (response != 'n' && response != 'y');
            again = (response == 'y');

        } while (again);

        System.out.println("Process Completed.");
    }
}
