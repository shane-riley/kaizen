import java.util.Random;

/**
 * A Monte Carlo Analysis of the Birthday Paradox
 * Class: CIT 130
 * Date: 07/01/2020
 * @author Shane Riley
 * @version 1.0
 */

public class BirthdayParadox
{
//    Set helper class
    public static class BirthdaySet
    {
//        Node helper for Set
        private class Node
        {
            private int value;
            private Node link;

            public Node()
            {
                value = 0;
                link = null;
            }

            public Node(int newValue, Node newLink)
            {
                value = newValue;
                link = newLink;
            }
        } // end helper

        private Node head;

        private BirthdaySet()
        {
            head = null;
        }

        /**
         * Add a new element to the set. Return false if item already exists in set
         */
        public boolean add(int newDay)
        {
            if (!contains(newDay))
            {
                head = new Node(newDay, head);
                return true;
            }
            return false;
        }

        /**
         * Check to see if element exists in set
         */
        public boolean contains(int newDay)
        {
            Node position = head;
            int itemAtPosition;
            while (position != null)
            {
                itemAtPosition = position.value;
                if (itemAtPosition == newDay)
                    return true;
                position = position.link;
            }
            return false;
        }
    }

    //    One iteration method (returns boolean indicating collision)
    private static boolean runIteration(int numPeople)
    {
//        Make new set
        BirthdaySet mySet = new BirthdaySet();
        int newDay;
        Random rand = new Random();
        for (int i = 0; i < numPeople; i++)
        {
            newDay = rand.nextInt(365); // 0 to 364
            if (!mySet.add(newDay))
                return true; // collision
        }
        return false; // no collision
    }

//    All Iterations method (returns collisions)
    private static int runAllIterations(int numPeople, int iterations)
    {
        int collisions = 0;

        for (int iteration = 0; iteration < iterations; iteration++)
        {
            if (runIteration(numPeople))
                collisions++;
        }
        return collisions;
    }

//    Main method
    public static void main(String[] args)
    {
        int iterations = 100000;
        int[] people = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

        double probability;
        int collisions;

        for(int numPeople : people)
        {
            collisions = runAllIterations(numPeople, iterations);
            probability = (double) collisions / iterations;
            System.out.println("After " + iterations + " tests there were " + collisions
                    + " occurrences of shared birthdays in a set of " + numPeople + " people.");
            System.out.println("Probability: " + probability);
        }

        System.out.println();
        System.out.println("Process Completed.");
    }
}
