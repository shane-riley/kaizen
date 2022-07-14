import java.io.PrintWriter;
import java.io.FileOutputStream;
import java.io.FileNotFoundException;

/**
 * Copied from text
 * Class: CIT 130
 * Date: 06/15/2020
 */

public class TextFileOutputDemo
{
    public static void main(String[] args)
    {
        PrintWriter outputStream = null;
        try
        {
            outputStream =
                    new PrintWriter(new FileOutputStream("morestuff.txt"));
        }
        catch (FileNotFoundException e)
        {
            System.out.println("Error opening the file morestuff.txt");
            System.exit(0);
        }

        System.out.println("Writing to file.");
        outputStream.println("1 2 3");
        outputStream.println("This is the second line.");
        outputStream.close();
        System.out.println("End of program.");
    }
}
