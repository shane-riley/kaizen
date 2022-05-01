import java.util.Scanner;

public class spr33_lab4C {

    public static void main(String[] args) {
        

        // Variables
        int MIN_RANGE = 30;
        int MAX_RANGE = 40;

        String[] welcomeStrings = {
            "Hello user",
            "Welcome to my little game: ~~~~ The right input ~~~~ ",
            "The rules are simple! Just input a number between 30 and 40!"};

        String promptString = "What's your number? ";
        String wrongString = "Try again :(";
        String rightString = "Correct!!!";
        int guess;

        
        Scanner kb = new Scanner(System.in);



        // Print welcome
        for (String row: welcomeStrings) {
            System.out.println(row);
        }

        while (true) {
            
            // Prompt for input
            System.out.print(promptString);
            guess = kb.nextInt();
            kb.nextLine();

            if ((guess < MIN_RANGE) || (guess > MAX_RANGE)) {
                // Say wrong, repeat
                System.out.println(wrongString);
                continue;
            }

            break;
        }

        // Game won
        System.out.println(rightString);
    }
}