import java.util.Random;

/**
 * Copied from text
 * Class: CIT 130
 * Date: 05/29/2020
 */

public class CoinFlipDemo
{
    public static final int FINAL = 5;
    public static void main(String[] args)
    {
        Random rng = new Random();
        int counter = 1;
        String message;

        while (counter <= FINAL)
        {
            System.out.print("Flip number " + counter + ": ");
            int coinFlip = rng.nextInt(2);
            if (coinFlip == 1)
                message = "Heads";
            else
                message = "Tails";
            System.out.println(message);
            counter++;
        }
    }
}
