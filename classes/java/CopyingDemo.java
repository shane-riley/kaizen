/**
 * Copied from text
 * Class: CIT 130
 * Date: 06/06/2020
 */

public class CopyingDemo
{
    public static void main(String[] args)
    {
        Sale[] a = new Sale[2];
        a[0] = new Sale("atomic coffee mug", 130.00);
        a[1] = new DiscountSale("invisible paint", 5.00, 10); // this is legal bc it is also of class type Sale
        int i;

        Sale[] b = badCopy(a);

        System.out.println("With copy constructors:");
        for (i = 0; i < a.length; i++)
        {
            System.out.println("a[" + i + "] = " + a[i]);
            System.out.println("b[" + i + "] = " + b[i]);
            System.out.println();
        }

//        b = goodCopy(a);

        System.out.println("With clone method:");
        for (i = 0; i < a.length; i++)
        {
            System.out.println("a[" + i + "] = " + a[i]);
            System.out.println("b[" + i + "] = " + b[i]);
            System.out.println();
        }
    }

    public static Sale[] badCopy(Sale[] a)
    {
        Sale[] b = new Sale[a.length];
        for (int i = 0; i < a.length; i++)
            b[i] = new Sale(a[i]); // The DiscountSale object is going to get upcast!!!!
        return b;
    }

//    public static Sale[] goodCopy(Sale[] a)
//    {
//        Sale[] b = new Sale[a.length];
//        for (int i = 0; i < a.length; i++)
//            b[i] = (Sale) a[i].clone(); // I didn't override clone, so this won't work until chapter 13 lol
//        return b;
//    }
}
