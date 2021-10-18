import java.util.Arrays;

/**
 * An implementation of the Towers of Hanoi done recursively
 * Class: CIT 130
 * Date: 06/18/2020
 * @author Shane Riley
 * @version 1.0
 */

public class TowersOfHanoi
{
    private final int numPegs = 3;
    private int height;
    private int[][] towers;

//    Constructor
    public TowersOfHanoi(int inputHeight)
    {
//        Positive integer precondition
        if (inputHeight < 1)
        {
            System.out.println("Height must be greater than zero!");
            System.exit(0);
        }
        else
        {
//            Build arrays
            height = inputHeight;
            towers = new int[numPegs][inputHeight];
            for (int i = 0; i < towers[0].length; i++)
            {
                towers[0][i] = inputHeight - i;
            }
            Arrays.fill(towers[1], 0);
            Arrays.fill(towers[2], 0);
        }
    }

//    Find last nonzero element of 1D array (-1 if empty)
    public static int top(int[] arr)
    {
        for (int i = 0; i < arr.length; i++)
        {
            if (arr[i] == 0)
            {
                if (i == 0)
                    return -1;
                else
                    return i - 1;
            }
        }
        return arr.length - 1;
    }


//    Move (recursive)
    public void move(int n, int from, int to, int using)
    {
        if (n > 0) {
//            Move all but one disk from -> using
            move(n - 1, from, using, to);

//            Move last disk from -> to
//            Find indexes
            int from_index = top(towers[from]);
            int to_index = top(towers[to]) + 1;

            if (from_index < 0) {
                System.out.println("Tried to grab from empty tower. Exiting...");
                System.exit(0);
            }

//            Perform move
            int temp = towers[from][from_index];
            towers[to][to_index] = temp;
            towers[from][from_index] = 0;

//            Display the change
            printArrays();

//            Move other disks using -> to
            move(n - 1, using, to, from);
        }
    }

//    Display towers
    public void printArrays()
    {
        for (int i = 0; i < towers.length; i++)
        {
            for (int j = 0; j < towers[i].length; j++)
                System.out.print(towers[i][j] + " ");
            System.out.println();
        }
        System.out.println();
    }

    public static void main(String[] args)
    {
        int towerHeight = 5;
        TowersOfHanoi toh = new TowersOfHanoi(towerHeight);

        System.out.println("Towers of Hanoi with height: " + towerHeight);
        System.out.println();
        toh.printArrays();
        toh.move(towerHeight, 0, 2, 1);
        System.out.println("Process Completed");
    }
}
