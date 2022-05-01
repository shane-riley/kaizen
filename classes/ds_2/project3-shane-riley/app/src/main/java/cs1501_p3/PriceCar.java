/**
 * PriceCar specification for CS1501 Project 3
 * @author	Shane Riley
 */
package cs1501_p3;

public class PriceCar extends Car implements Comparable<PriceCar> {

    // Constructor
    public PriceCar(String newVin, String newMake, String newModel) {
        super(newVin, newMake, newModel);
    }

    // Compare
    public int compareTo(PriceCar other) {
        if (this.getPrice() > other.getPrice()) {
            return 1;
        } else if (this.getPrice() < other.getPrice()) {
            return -1;
        } else {
            return 0;
        }
    }

}
