import java.util.Random;

/**
 * A class for testing various sorting algs
 * 
 * @author Shane Riley
 * @version 1.0
 * @since 4/11/2021
 */

// Test Alg helper
public class TestAlg {

    private static final int SEED = 123456789;
    private static final int UPPER_BOUND = 1000000000;

    // Instance
    private Sorter alg;
    private String name;
    private double avgTimeBest, avgTimeWorst;
    private int minRecBest, minRecWorst;

    // Const
    public TestAlg(Sorter al, String n, int arraySize, int numRunsPerConfig, boolean isSorted) {
        alg = al;
        name = n;
        avgTimeBest = 100;
        avgTimeWorst = 0;
        this.run(arraySize, numRunsPerConfig, isSorted);
    }

    // Runner
    private void run(int arraySize, int numRunsPerConfig, boolean isSorted) { 

        // Iterate through min rec
        for (int minRec = 5; minRec <= 75; minRec+=10) {

            // Build the data
            Integer[] a = new Integer[arraySize];
            Random rd = new Random(SEED);
            double totalTime = 0;

            // Iterate through num runs
            for (int runNum = 0; runNum < numRunsPerConfig; runNum++) {

                // Seed array
                for (int i = 0; i < arraySize; i++) {
                    if (isSorted) {
                        a[i] = (i+1);
                    } else {
                        a[i] = rd.nextInt(UPPER_BOUND);
                    }
                }

                // 
                alg.setMin(minRec);

                // Time and run sort
                long start = System.nanoTime();
                alg.sort(a, a.length);
                long end = System.nanoTime();
                double timeTaken = (double) (end-start) / 1000000000;

                // Running total
                totalTime += timeTaken;
            }

            double avgTime = totalTime/numRunsPerConfig;

            // Check best
            if (avgTime < avgTimeBest) {
                avgTimeBest = avgTime;
                minRecBest = minRec;
            }

            // Check worst
            if (avgTime > avgTimeWorst) {
                avgTimeWorst = avgTime;
                minRecWorst = minRec;
            }
        }
    }

    // getbesttime
    public double getBestAvgTime() { return this.avgTimeBest; }

    // getworsttime
    public double getWorstAvgTime() { return this.avgTimeWorst; }

    // getbestrec
    public int getBestMinRec() { return this.minRecBest; }

    // getworstrec
    public int getWorstMinRec() { return this.minRecWorst; }

    // getname
    public String getName() { return this.name; };

    // Display result
    public void displayResult() {
        System.out.println("Algorithm: " + this.name);
        System.out.println("\tBest Result:");
        System.out.println("\t\tMin Recurse: " + this.minRecBest);
        System.out.println("\t\tAverage: " + this.avgTimeBest + " sec");
        System.out.println("\tWorst Result:");
        System.out.println("\t\tMin Recurse: " + this.minRecWorst);
        System.out.println("\t\tAverage: " + this.avgTimeWorst + " sec");
    }
}
