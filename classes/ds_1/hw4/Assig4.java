import java.util.Scanner;
import java.util.Random;

/**
 * A main for testing sorting algs
 * 
 * @author Shane Riley
 * @version 1.0
 * @since 4/11/2021
 */

public class Assig4 {

    // Main
    public static void main(String[] args) {
        

        // Unload args
        // if (args.length < 3) {System.out.println("Missing arguments!"); System.exit(0);}
        // else
        int arraySize, numRunsPerConfig;
        boolean isSorted;
        arraySize = Integer.parseInt(args[0]);  // Turns String into an int
        numRunsPerConfig = Integer.parseInt(args[1]);
        isSorted = Boolean.parseBoolean(args[2]);


        Sorter[] algs = {   
            new QuickSort<Integer>(new SimplePivot<Integer>()),
            new QuickSort<Integer>(new MedOfThree<Integer>()),
            new QuickSort<Integer>(new RandomPivot<Integer>()),
            new MergeSort<Integer>()
        };

        String[] algNames = {
            "Simple Pivot Quicksort",
            "Median of Three Quicksort",
            "Random Pivot Quicksort",
            "MergeSort"
        };

        TestAlg[] algTests = new TestAlg[algs.length];

        // Display initialization information
        System.out.println("Initialization information:");
        System.out.println("\tArray size: " + arraySize);
        System.out.println("\tNumber of runs per test: " + numRunsPerConfig);
        System.out.println("\tInitial data: " + ((isSorted) ? "Sorted" : "Random"));
        System.out.println("");

        // Run alg tests

        for (int algNum = 0; algNum < algs.length; algNum++) {
            algTests[algNum] = new TestAlg(algs[algNum], algNames[algNum], arraySize, numRunsPerConfig, isSorted);
        }

        // Find best overall
        double avgTimeBest = 100;
        double avgTimeWorst = 0;
        int indexOfBest = -1;
        int indexOfWorst = -1;

        // Find best and worst
        for (int i = 0; i < algs.length; i++) {
            if (algTests[i].getBestAvgTime() < avgTimeBest) { indexOfBest = i; avgTimeBest = algTests[i].getBestAvgTime(); }
            if (algTests[i].getWorstAvgTime() > avgTimeWorst) { indexOfWorst = i; avgTimeWorst = algTests[i].getWorstAvgTime(); }
        }

        // Prints
        System.out.println("After the tests, here is the best setup:");
        System.out.println("\tAlgorithm: " + algTests[indexOfBest].getName());
        System.out.println("\tData Status: " + ((isSorted) ? "Sorted" : "Random"));
        System.out.println("\tMin Recurse: " + algTests[indexOfBest].getBestMinRec());
        System.out.println("\tAverage: " + algTests[indexOfBest].getBestAvgTime());
        System.out.println("");
        System.out.println("After the tests, here is the worst setup:");
        System.out.println("\tAlgorithm: " + algTests[indexOfWorst].getName());
        System.out.println("\tData Status: " + ((isSorted) ? "Sorted" : "Random"));
        System.out.println("\tMin Recurse: " + algTests[indexOfWorst].getWorstMinRec());
        System.out.println("\tAverage: " + algTests[indexOfWorst].getWorstAvgTime());
        System.out.println("");

        System.out.println("Here are the per algorithm results:");
        for (int i = 0; i < algs.length; i++) {
            algTests[i].displayResult();
            System.out.println("");
        }



    }

}
