/**
 * Copied from text
 * Class: CIT 130
 * Date: 06/29/2020
 */

public class UnorderedPairDemo
{
    public static void main(String[] args)
    {
        UnorderedPair<String> p1 =
                new UnorderedPair<String>("peanuts", "beer");
        UnorderedPair<String> p2 =
                new UnorderedPair<String>("beer", "peanuts");
        if (p1.equals(p2))
        {
            System.out.println("The mixed unordered pairs are working.");
        }
    }
}
