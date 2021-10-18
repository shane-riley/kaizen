import java.util.HashSet;
import java.util.Iterator;

/**
 * Copied from text
 * Class: CIT 130
 * Date: 07/01/2020
 */

public class HashSetDemo
{
    private static void outputSet(HashSet<String> set)
    {
        Iterator<String> i = set.iterator();
        while (i.hasNext())
            System.out.print(i.next() + " ");
        System.out.println();
    }

    public static void main(String[] args)
    {
        HashSet<String> round = new HashSet<String>();
        HashSet<String> green = new HashSet<String>();

        round.add("peas");
        round.add("ball");
        round.add("pie");
        round.add("grapes");

        green.add("peas");
        green.add("grapes");
        green.add("garden hose");
        green.add("grass");

        System.out.println("Contents of set round: ");
        outputSet(round);

        System.out.println("\nContents of set green: ");
        outputSet(green);

        HashSet<String>setUnion = new HashSet<>(round);
        setUnion.addAll(green);
        System.out.println("\nUnion of green and round:");
        outputSet(setUnion);

        HashSet<String>setInter = new HashSet<>(round);
        setInter.removeAll(green);
        System.out.println("\nIntersection of green and round:");
        outputSet(setInter);

    }
}
