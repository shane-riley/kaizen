/**
 * A class implementation of a blackjack cards for ds_1 Assignment 1
 * 
 * @author Shane Riley
 * @version 1.0
 * @since 2/4/2021
 */

public class BlackjackCards extends RandIndexQueue<Card> {
    
    // Empty constructor
    public BlackjackCards(int inputSize) {
        super(inputSize);
    }

    // Load with decks
    public void loadShoe(int numDecks) {
        for (int i=0; i<numDecks; i++) {
            // Add a deck
            for (Card.Suits suit: Card.Suits.values()) {
                for (Card.Ranks rank: Card.Ranks.values()) {
                    Card c = new Card(suit, rank);
                    this.enqueue(c);
                }
            }
        }

        // Shuffle
        this.shuffle();
    }

    // getValue
    public int getValue() {
        int value = 0;
        int numAces = 0;
        // Add not aces, then loop back through aces
        for (int i = 0; i < this.size(); i++) {

            Card c = this.get(i);

            if (c.value() == 11) {
                // Ace, don't adjust value yet
                numAces++;
            } else {
                // Add to the value
                value += c.value();
            }
        }
        
        for (int j = 0; j < numAces; j++) {
            value += (value > 10) ? 1 : 11;
        }
        return value;
    }

    // toString
    public String toString() {
        return super.toString() + " : " + this.getValue();
    }
}
