import java.util.Scanner;
import java.io.FileInputStream;
import java.io.FileNotFoundException;

/**
 * Copied from text
 * Class: CIT 130
 * Date: 05/29/2020
 */

public class TextFileDemo {
    public static void main(String[] args) {
        Scanner fileIn = null;
        try {
            fileIn = new Scanner(
                    new FileInputStream("test.txt"));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } {
            System.out.println("File not found.");
            System.exit(0);
        }

        int high_score;
        String name;

        System.out.println("Text left to read? " +
                fileIn.hasNextLine());
        high_score = fileIn.nextInt();
        fileIn.nextLine();
        name = fileIn.nextLine();

        System.out.println("Name: " + name);
        System.out.println("High score: " + high_score);
        System.out.println("Text left to read? " + fileIn.hasNextLine());
        fileIn.close();
    }
}
