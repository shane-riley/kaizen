/**
 * A testing class for Counter
 * Class: CIT 130
 * Date: 05/26/2020
 * @author Shane Riley
 * @version 1.0
 */

public class CounterHarness {
    public static void main(String[] args) {

//        Set counter to zero
        Counter c1 = new Counter();
        System.out.println("Counter with zero running toString:");
        System.out.println(c1.toString());

//        Set second counter to 5
        Counter c2 = new Counter(5);
        System.out.println("Counter with five running toString:");
        System.out.println(c2.toString());

//        Add four to c1
        c1.Increment(4);

//        Check equality
        System.out.println("Checking equality between non-equal objects:");
        System.out.println(c1.equals(c2));

//        Add one to c1
        c1.Increment();

//        Check equality
        System.out.println("Checking equality between equal objects:");
        System.out.println(c1.equals(c2));

//        Subtract one from c2
        c2.Decrement();
        System.out.println("Counter with four running toString:");
        System.out.println(c2.toString());

//        Attempt to subtract 6 from c1
        c1.Decrement(6);

//        Assure non-negative number present
        System.out.println("Assure that counter is still 5");
        System.out.println(c1.toString());

//        Subtract 5 from c1
        c1.Decrement(5);
        System.out.println("Assure that counter is now 0");
        System.out.println(c1.toString());

//        Attempt to subtract 1 from c1
        c1.Decrement();

//        Assure non-negative number present
        System.out.println("Assure that counter is still 0");
        System.out.println(c1.toString());

//        Check string concatenation
        System.out.println("Check string concatenation:");
        System.out.println("Look! A(n) " + c2);

        System.out.println("Harness run completed.");
    }
}
