import java.io.*;
import java.util.Scanner;

/**
 * A class for reading and writing to files (text or binary)
 * Class: CIT 130
 * Date: 06/15/2020
 * @author Shane Riley
 * @version 1.0
 */

public class BasicPrintWrite {

    //    Print text file
    private static void printTextFile(String filename) throws FileNotFoundException
    {
//        Open file
        Scanner inputStream = new Scanner(new FileInputStream(filename));
        System.out.println(filename + " opened. Contents:");

//        Print file
        while(inputStream.hasNextLine())
        {
            System.out.println(inputStream.nextLine());
        }
//        End of file
        inputStream.close();
    }

    //    Print binary file
    private static void printBinaryFile(String filename) throws IOException
    {
//        Open file
        ObjectInputStream inputStream = new ObjectInputStream(new FileInputStream(filename));
        System.out.println(filename + " opened. Contents:");

//        Print file
        try {
            while (true) System.out.println(inputStream.readUTF());
        } catch (EOFException e) {
//            End of file
            inputStream.close();
        }
    }

//    Write text file
    private static void writeTextFile(String filename) throws FileNotFoundException
    {
//        Open file
        PrintWriter outputStream = new PrintWriter(new FileOutputStream(filename));
        Scanner keyboard = new Scanner(System.in);
        System.out.println(filename + " opened and cleared. Enter line:");

        boolean again = true;
        String line;
        char response;
        do {
//            Enter a line
            System.out.print("> ");
            line = keyboard.nextLine();
            outputStream.println(line);
            do {
                System.out.print("Saved. Another line? (y/n): ");
                response = Character.toLowerCase(keyboard.next().charAt(0));
                keyboard.nextLine(); // clear scanner
                if (response == 'n') again = false;
            } while (response != 'y' && response != 'n');
        } while (again);
        outputStream.close();
    }

//    Write binary file
    private static void writeBinaryFile(String filename) throws IOException
    {
//        Open file
        ObjectOutputStream outputStream = new ObjectOutputStream(new FileOutputStream(filename));
        Scanner keyboard = new Scanner(System.in);
        System.out.println(filename + " opened and cleared. Enter line:");

        boolean again = true;
        String line;
        char response;

        do {
//            Enter a line
            System.out.print("> ");
            line = keyboard.nextLine();
            outputStream.writeUTF(line);
            do {
                System.out.print("Saved. Another line? (y/n): ");
                response = Character.toLowerCase(keyboard.next().charAt(0));
                keyboard.nextLine(); // clear scanner
                if (response == 'n') again = false;
            } while (response != 'y' && response != 'n');
        } while (again);
        outputStream.close();
    }

    //    Print file
    public static void printFile(String filename, char fileType)
    {
//        Run appropriate method based on file type
        if (fileType == 't')
        {
            try {
                printTextFile(filename);
            } catch(FileNotFoundException e) {
                System.out.println(filename + " not found");
            }
        }
        else if (fileType == 'b')
        {
            try {
                printBinaryFile(filename);
            } catch (FileNotFoundException e) {
                System.out.println(filename + " not found");
            } catch (IOException e) {
                System.out.println("Error reading file.");
            }
        }
        else
        {
            System.out.println("Invalid mode");
        }
    }

//    Write file
    public static void writeFile(String filename, char fileType)
    {
//        Run appropriate method based on file type
        if (fileType == 't')
        {
            try {
                writeTextFile(filename);
            } catch(FileNotFoundException e) {
                System.out.println(filename + " not found");
            }
        }
        else if (fileType == 'b')
        {
            try {
                writeBinaryFile(filename);
            } catch (FileNotFoundException e) {
                System.out.println(filename + " not found");
            } catch (IOException e) {
                System.out.println("File error.");
            }
        }
        else
        {
            System.out.println("Invalid mode");
        }
    }

//    main testing method
    public static void main(String[] args)
    {
        char response, mode, readwrite;
        boolean again = true;
        String filename;
        Scanner keyboard = new Scanner(System.in);

        System.out.println("Shane's File IO program.");
        System.out.println();
        do {
//            Gather information
            System.out.print("Enter the file name: ");
            filename = keyboard.nextLine();
            do {
                System.out.print("Choose binary or text (b/t): ");
                mode = Character.toLowerCase(keyboard.next().charAt(0));
                keyboard.nextLine(); // clear scanner
            } while (mode != 'b' && mode != 't');
            do {
                System.out.print("Choose read or write (r/w): ");
                readwrite = Character.toLowerCase(keyboard.next().charAt(0));
                keyboard.nextLine(); // clear scanner
            } while (readwrite != 'r' && readwrite != 'w');
            System.out.println();

//            Run with proper settings
            if (readwrite == 'r') {
                printFile(filename, mode);
            } else {
                writeFile(filename, mode);
            }

//            Ask whether to continue
            System.out.println();
            do {
                System.out.print("Continue running? (y/n): ");
                response = Character.toLowerCase(keyboard.next().charAt(0));
                keyboard.nextLine(); // clear scanner
                if (response == 'n') again = false;
            } while (response != 'y' && response != 'n');
        } while(again);

//        End program
        System.out.println("Process completed.");
    }
}
