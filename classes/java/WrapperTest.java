/**
 * Test class for WrapperShallow and WrapperDeep
 * Class: CIT 130
 * Date: 06/07/2020
 * @author Shane Riley
 * @version 1.0
 */

public class WrapperTest
{
    public static void main(String[] args)
    {
//        WrapperShallow
        System.out.println("*** STARTING int[] WRAPPER CLASS TEST ***");
        System.out.println();
        System.out.println("USING WrapperShallow:");
        System.out.println();

//        Create shallow object
        WrapperShallow ws1 = new WrapperShallow(new int[] {1, 2, 3});
        System.out.println("Initial shallow object: " + ws1.toString());

//        Make copy
        WrapperShallow ws2 = new WrapperShallow(ws1);
        System.out.println("Copy shallow object: " + ws2.toString());

//        Change initial
        ws1.setArray(new int[] {4, 5, 6});
        System.out.println("Initial shallow object set to: " + ws1.toString());
        System.out.println("Copy shallow object is now: " + ws2.toString());

//        Compare
        System.out.println("If the objects share a reference, they will still be equal");
        System.out.println("ws1.equals(ws2) = " + ws1.equals(ws2));

//        WrapperDeep
        System.out.println();
        System.out.println("USING WrapperDeep:");
        System.out.println();

//        Create deep object
        WrapperDeep wd1 = new WrapperDeep(new int[] {1, 2, 3});
        System.out.println("Initial deep object: " + wd1.toString());

//        Make copy
        WrapperDeep wd2 = new WrapperDeep(wd1);
        System.out.println("Copy deep object: " + wd2.toString());

//        Change initial
        wd1.setArray(new int[] {4, 5, 6});
        System.out.println("Initial deep object set to: " + wd1.toString());
        System.out.println("Copy deep object is now: " + wd2.toString());

//        Compare
        System.out.println("If the objects share a reference, they will still be equal");
        System.out.println("wd1.equals(wd2) = " + wd1.equals(wd2));

        System.out.println();
        System.out.println("Main completed.");
    }
}
