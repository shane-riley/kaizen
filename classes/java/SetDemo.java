/**
 * Copied from text
 * Class: CIT 130
 * Date: 07/01/2020
 */

public class SetDemo
{
    public static void main(String[] args)
    {
        Set round = new Set<String>();
        Set green = new Set<String>();
        round.add("peas");
        round.add("ball");
        round.add("pie");
        round.add("grapes");

        green.add("peas");
        green.add("grapes");
        green.add("garden hose");
        green.add("grass");

        System.out.println("Contents of set round: ");
        round.output();

        System.out.println("Contents of set green: ");
        green.output();
        System.out.println();

        System.out.println("ball in set round? " +
                round.contains("ball"));
        System.out.println("ball in set green? " +
                green.contains("ball"));
        System.out.println("ball and peas in same set? " +
               ((round.contains("ball") &&
                (round.contains("peas"))) ||
                (green.contains("ball") &&
                (green.contains("peas")))));

        System.out.println("pie and grass in same set? " +
                ((round.contains("pie") &&
                (round.contains("grass"))) ||
                (green.contains("pie") &&
                (green.contains("grass")))));

        System.out.println("Union of green and round: ");
        round.union(green).output();
        System.out.println("Intersection of green and round: ");
        round.intersection(green).output();
    }
}
