import java.io.File;
import java.io.PrintStream;
import java.io.FileOutputStream;
import java.io.FileNotFoundException;

/**
 * Copied from text
 * Class: CIT 130
 * Date: 06/15/2020
 */

public class RedirectionDemo
{
    public static void main(String[] args)
    {
        PrintStream errStream = null; //for scope
        try
        {
            errStream =
                    new PrintStream(
                            new FileOutputStream("errormessages.txt"));
        }
        catch(FileNotFoundException e)
        {
            System.out.println(
                    "Error opening file with FileOutputStream.");
            System.exit(0);
        }
        System.setErr(errStream);

        System.err.println("Hello from System.err");
        System.out.println("Hello from System.out");
        System.err.println("Hello from System.err again");
        errStream.close(); //manual streams must be closed
    }
}
