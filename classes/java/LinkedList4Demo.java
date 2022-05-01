/**
 * Demo for LinkedList4
 * Class: CIT 130
 * Date: 07/01/2020
 * @author Shane Riley
 * @version 1.0
 */

public class LinkedList4Demo
{
    public static void main(String[] args)
    {
        // Build Linked List using ListEntry class
        LinkedList4<ListEntry> myList = new LinkedList4<>();
        String[] testStrings = {"Apples", "Bananas", "Dragonfruits", "Peaches", "Melons"};
        for (String testString : testStrings)
            myList.addToStart(new ListEntry(testString));


//        Print list
        System.out.println("Filled Linked List:");
        System.out.println(myList.toString());
        System.out.println();

        System.out.println("Printed Backwards:");
        myList.outputBackwards();
        System.out.println();

//        Print using iterator
        System.out.println("Print list using an iterator");
        LinkedList4<ListEntry>.Iterator<ListEntry> i = myList.iterator();

        while(i.hasNext())
        {
            System.out.print(i.next() + " ");
        }
        System.out.println();
        System.out.println();

//        Copy List using clone and using copy constructor
        System.out.println("Copy using clone:");
        LinkedList4<ListEntry> myListCloned = myList.clone();
        System.out.println(myListCloned.toString());
        System.out.println();

        System.out.println("Copy using Copy Constructor:");
        LinkedList4 myListConstructed = new LinkedList4(myList);
        System.out.println(myListConstructed.toString());
        System.out.println();

        System.out.println("Shorten original List:");
        myList.deleteHeadNode();
        System.out.println(myList.toString());
        System.out.println();

        System.out.println("Location of melons still in cloned list:");
        ListEntry le = new ListEntry("Melons");
        System.out.println(myListCloned.findData(le) != null);
        System.out.println();

        System.out.println("Location of melons still in copy constructed list:");
        le = new ListEntry("Melons");
        System.out.println(myListConstructed.findData(le) != null);
        System.out.println();

        System.out.println("Print original list backwards:");
        myList.outputBackwards();
        System.out.println();

        System.out.println("Clear original list:");
        while (myList.deleteHeadNode());
        System.out.println();

        System.out.println("Old list should be empty: " + myList.toString());
        System.out.println();

        System.out.println("Cloned List:");
        System.out.println(myListCloned.toString());
        System.out.println();

        System.out.println("Copy Constructed List:");
        System.out.println(myListConstructed.toString());
    }
}
