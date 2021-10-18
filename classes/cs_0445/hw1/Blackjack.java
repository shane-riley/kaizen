/**
 * Blackjack batch runner for CS 0445 Assignment 1
 * 
 * @author Shane Riley
 * @version 1.0
 * @since 2/4/2021
 */

public class Blackjack {
    public static void main(String args[]) {

        // Unpack run arguments
        int numRounds = Integer.parseInt(args[0]);
        int numDecks = Integer.parseInt(args[1]);
        int numTrace = Integer.parseInt(args[2]);
        
        // For debug
        // int numRounds = 200;
        // int numDecks = 5;
        // int numTrace = 10;

        // Play game
        Blackjack game = new Blackjack(numRounds, numDecks, numTrace);
        game.play();
    }

    // Instance variables
    private int numRounds;
    private int numDecks;
    private int numTrace;
    private int playerWins;
    private int dealerWins;
    private int pushes;

    private BlackjackCards deck;
    private BlackjackCards discard;
    private BlackjackCards playerHand;
    private BlackjackCards dealerHand;

    // Constructor
    public Blackjack(int inRounds, int inDecks, int inTrace) {
        numRounds = inRounds;
        numDecks = inDecks;
        numTrace = inTrace;

        playerHand = new BlackjackCards(10);
        dealerHand = new BlackjackCards(10);
        discard = new BlackjackCards(52 * inDecks);
        deck = new BlackjackCards(52 * (inDecks + 1));

        // Load deck
        deck.loadShoe(numDecks);
    }

    // Run all
    public void play() {
        System.out.println("Starting Blackjack with " + numRounds + " and " + numDecks + " decks in the shoe");
        System.out.println("");

        boolean doTrace;
        for (int currentRound = 1; currentRound <= numRounds; currentRound++) {
            doTrace = (currentRound <= numTrace);
            this.runRound(doTrace);

            if (doTrace) {System.out.println(); System.out.println();}

            // Check for shuffle
            if (discard.size() > 3 * deck.size()) {
                while (discard.size() > 0) {
                    deck.enqueue(discard.dequeue());
                }
                deck.shuffle();
                System.out.println("Reshuffling the shoe in round " + currentRound);
                System.out.println();
                assert discard.size() == 0;
                discard.clear();
            }

            assert (deck.size() + discard.size()) == 52 * numDecks;
        }

        

        System.out.println("After " + numRounds + " rounds, here are the results:");
        System.out.println("\tDealer Wins: " + dealerWins);
        System.out.println("\tPlayer Wins: " + playerWins);
        System.out.println("\tPushes: " + pushes);
    }

    // Run round
    private void runRound(boolean doTrace) {
        // Deal cards
        playerHand.enqueue(deck.dequeue());
        dealerHand.enqueue(deck.dequeue());
        playerHand.enqueue(deck.dequeue());
        dealerHand.enqueue(deck.dequeue());

        if (doTrace) {
            System.out.println("Player: " + playerHand.toString());
            System.out.println("Dealer: " + dealerHand.toString());
        }

        // Check for blackjack win
        if (playerHand.getValue() == dealerHand.getValue() && playerHand.getValue() == 21) {
            if (doTrace) System.out.println("Result: Push!");
            this.cleanHands();
            pushes++;
            return;
        }
        else if (playerHand.getValue() == 21) {
            if (doTrace) System.out.println("Result: Player Blackjack wins!");
            this.cleanHands();
            playerWins++;
            return;
        }
        else if (dealerHand.getValue() == 21) {
            if (doTrace) System.out.println("Result: Dealer Blackjack wins!");
            this.cleanHands();
            dealerWins++;
            return;
        }

        // Player plays
        while (playerHand.getValue() < 17) {
            // HIT!
            Card newCard = deck.dequeue();
            if (doTrace) System.out.println("Player hits: " + newCard.toString());
            playerHand.enqueue(newCard);
        }

        // Player stand or bust?
        if (16 < playerHand.getValue() && playerHand.getValue() < 22) {
            // Player stands
            if (doTrace) System.out.println("Player STANDS: " + playerHand.toString());
        } else {
            if (doTrace) System.out.println("Player BUSTS: " + playerHand.toString());
            if (doTrace) System.out.println("Result: Dealer wins!");
            this.cleanHands();
            dealerWins++;
            return;
        }

        // Dealer plays
        while (dealerHand.getValue() < 17) {
            // HIT!
            Card newCard = deck.dequeue();
            if (doTrace) System.out.println("Dealer hits: " + newCard.toString());
            dealerHand.enqueue(newCard);
        }

        // Dealer check
        if (16 < dealerHand.getValue() && dealerHand.getValue() < 22) {
            // Player stands
            if (doTrace) System.out.println("Dealer STANDS: " + dealerHand.toString());
        } else {
            if (doTrace) System.out.println("Dealer BUSTS: " + dealerHand.toString());
            if (doTrace) System.out.println("Result: Player wins!");
            this.cleanHands();
            playerWins++;
            return;
        }

        // If game not over, run final check
        if (playerHand.getValue() > dealerHand.getValue()) {
            if (doTrace) System.out.println("Result: Player wins!");
            this.cleanHands();
            playerWins++;
            return;
        }
        else if (dealerHand.getValue() > playerHand.getValue()) {
            if (doTrace) System.out.println("Result: Dealer wins!");
            this.cleanHands();
            dealerWins++;
            return;
        } else {
            if (doTrace) System.out.println("Result: Push!");
            this.cleanHands();
            pushes++;
            return;
        }
    }

    private void cleanHands() {
        // Cleanup
        while (playerHand.size() > 0) {
            discard.enqueue(playerHand.dequeue());
        }
        while (dealerHand.size() > 0) {
            discard.enqueue(dealerHand.dequeue());
        }
        assert dealerHand.size() == 0;
        assert playerHand.size() == 0;
        playerHand.clear();
        dealerHand.clear();

        // Check for dropped cards
        assert deck.size() + discard.size() == 52 * numDecks;
    }
}
