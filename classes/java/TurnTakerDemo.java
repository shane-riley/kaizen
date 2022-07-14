/**
 * Copied from text
 * Class: CIT 130
 * Date: 05/29/2020
 */

public class TurnTakerDemo
{
    public static void main(String[] args)
    {
        TurnTaker lover1 = new TurnTaker("Romeo", 1);
        TurnTaker lover2 = new TurnTaker("Juliet", 3);
        for (int i = 1; i < 5; i++)
        {
            System.out.println("Turn = " + TurnTaker.getTurn());
            if (lover1.isMyTurn())
                System.out.println("Love from " + lover1.getName());
            if (lover2.isMyTurn())
                System.out.println("Love from " + lover2.getName());
        }
    }
}
