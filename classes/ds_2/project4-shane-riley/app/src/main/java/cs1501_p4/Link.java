/**
 * Data class for containing link information (from location is implicit based on where the link is stored)
 * @author	Shane Riley
 */

package cs1501_p4;

public class Link {

    public final int COPPER_SPEED = 230000000;
    public final int FIBER_SPEED = 200000000;

    // Instance vars
    private int from;
    private int to;
    private boolean isCopper;
    private int bandwidth;
    private int length;

    // Constructor
    public Link(int from, int to, boolean isCopper, int bandwidth, int length) {
        this.from = from;
        this.to = to;
        this.isCopper = isCopper;
        this.bandwidth = bandwidth;
        this.length = length;
    }

    // Getters
    public int getTo() {
        return to;
    }

    public int getFrom() {
        return from;
    }

    public boolean getIsCopper() {
        return isCopper;
    }

    public int getBandwidth() {
        return bandwidth;
    }

    public int getLength() {
        return length;
    }

    public double getLatency() {
        // TODO: Double check me
        return (double) length / (isCopper ? COPPER_SPEED : FIBER_SPEED);
    }

    // Setters
    // TODO: Add if necessary

}
