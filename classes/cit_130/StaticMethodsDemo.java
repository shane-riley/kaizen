/**
 * Copied from text
 * Class: CIT 130
 * Date: 06/06/2020
 */

public class StaticMethodsDemo
{
    public static void main(String[] args)
    {
        Sale.announcement();
        DiscountSale.announcement();
        System.out.println(
                "That showed that you can override a static method " +
                        "definition.");
        Sale s = new Sale();
        DiscountSale discount = new DiscountSale();
        s.announcement(); // Interesting that IntelliJ sees the funny business going on
        discount.announcement();
        System.out.println("No surprises so far, but wait.");

        Sale discount2 = discount;
        System.out.println(
                "discount2 is a DiscountSale object in a Sale variable.");
        System.out.println("Which definition of announcement() will it use?");
        discount2.announcement();
        System.out.println("It used the Sale version of announcement()!");
    }
}
