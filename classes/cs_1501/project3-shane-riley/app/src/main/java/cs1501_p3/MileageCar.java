/**
 * MileageCar specification for CS1501 Project 3
 * @author	Shane Riley
 */
package cs1501_p3;

public class MileageCar extends Car implements Comparable<MileageCar> {

    // Constructor
    public MileageCar(String newVin, String newMake, String newModel) {
        super(newVin, newMake, newModel);
    }

    // Compare
    public int compareTo(MileageCar other) {
        if (this.getMileage() > other.getMileage()) {
            return 1;
        } else if (this.getMileage() < other.getMileage()) {
            return -1;
        } else {
            return 0;
        }
    }

}
