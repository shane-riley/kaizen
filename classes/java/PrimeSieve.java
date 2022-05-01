import java.util.Arrays;
import java.util.Scanner;

/**
 * An implementation of Sieve of Eratosthenes
 * Class: CIT 130
 * Date: 06/02/2020
 * @author Shane Riley
 * @version 1.0
 */

public class PrimeSieve {

    /**
     * A prime number array generator using the Sieve of Eratosthenes algorithm
     * @param max the upper limit of prime generation
     * @return int[] an array of prime numbers below or equal to max. Will return an empty array for max < 2
     */
    public static int[] getPrimes(int max)
    {
        int[] primes;

        if (max < 2)
        {
//            No primes; return an empty array
            primes = new int[]{};
            return primes;
        }

//        Create all-true boolean array of length max - 1
//        isPrime[0] pertains to 2, isPrime[1] to 3, all the way up to isPrime[isPrime.length - 1] to max
        boolean[] isPrime = new boolean[max - 1];
        Arrays.fill(isPrime, true);

//        Mark multiples of 2,3,5,7,...,n as false until 2 + n > sqrt(max)

        for (int factor = 2; factor <= Math.sqrt(max); factor++) {
//            Skip if factor is not two and even (redundant)
            if (factor % 2 == 0 && factor != 2)
                continue;

//            Mark multiples of the factor going up the array until max is exceeded
            int starting_index = (2 * factor) - 2;
            for (int i = starting_index; i < isPrime.length; i += factor)
                isPrime[i] = false;
        }


//        Grab number of primes found
        int count_primes = 0;
        for (boolean value : isPrime)
        {
            if (value)
                count_primes++;
        }

//        Create integer array and map values using isPrime
        primes = new int[count_primes]; // will always be large enough to store primes, since we checked

        int insert_primes = 0;
        for (int i = 0; i < isPrime.length; i++)
        {
            if (isPrime[i])
            {
                primes[insert_primes] = i + 2;
                insert_primes++;
            }
        }

//        Static method, so no deep copy required
        return primes;
    }

    /**
     * Main test method for getPrimes
     */

    public static void main(String[] args)
    {
        System.out.println("Testing of static getPrimes method:");

//        Testing code
//        int[] testValues = new int[] {-1, 0 ,1, 2, 3, 5, 7, 10, 20, 101};
//
//        for (int testValue : testValues) {
//            System.out.println("Primes evaluated to " + testValue + ":");
//            System.out.println(Arrays.toString(getPrimes(testValue)));
//        }

        Scanner keyboard = new Scanner(System.in);
        System.out.println("Please enter an inclusive maximum for prime number generation: ");
        int maximum = keyboard.nextInt();
        int[] primes = getPrimes(maximum);
        System.out.println("Primes to " + maximum + ":");
        System.out.println(Arrays.toString(primes));
        System.out.println(primes.length + " prime numbers found.");
        System.out.println("Program reached completion.");
    }
}
