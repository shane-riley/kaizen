/**
 * Copied from text
 * Class: CIT 130
 * Date: 06/30/2020
 */

public class LinkedList1Demo
{
    public static void main(String[] args)
    {
        LinkedList1 list = new LinkedList1();
        list.addToStart("Apples", 1);
        list.addToStart("Bananas", 2);
        list.addToStart("Cantaloupe", 3); // this is the head
        System.out.println("List had " + list.size() + " nodes.");
        list.outputList();

        if (list.contains("Cantaloupe"))
            System.out.println("Cantaloupe is on list.");
        else
            System.out.println("Cantaloupe is not on list.");

        list.deleteHeadNode();

        if (list.contains("Cantaloupe"))
            System.out.println("Cantaloupe is on list.");
        else
            System.out.println("Cantaloupe is not on list.");

        while (list.deleteHeadNode()); // this empties the list
        System.out.println("Start of list:");
        list.outputList();
        System.out.println("End of list.");
    }
}
