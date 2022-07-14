/**
 * A simple counter class (non-negative numbers only)
 * Class: CIT 130
 * Date: 05/26/2020
 * @author Shane Riley
 * @version 1.0
 */

public class Counter {

//    Internal count
    private int count;

//    Constructor to start count at zero
    public Counter() {
        setCount(0);
    }

//    Constructor to start count at input value
    public Counter(int input_count) {
        setCount(input_count);
    }

//    Get number
//    Only ever access count using this method
    public int getCount() {
        return count;
    }

//    Change number
//    By only ever changing the count through this method, we need only include one check
    public void setCount(int new_count) {
        if (new_count < 0) {
            System.out.println("Error: count cannot be set to non-negative number");
        } else {
            count = new_count;
        }
    }

//    Equality check
    public boolean equals(Counter counter_to_compare) {
        return this.getCount() == counter_to_compare.getCount();
    }

//    Return message describing object and state
    public String toString() {
        return "Instance of Counter with count: " + this.getCount();
    }

//    Add one
    public void Increment() {
        setCount(this.getCount() + 1);
    }

//    Add number
    public void Increment(int inc) {
        setCount(this.getCount() + inc);
    }

//    Subtract one
    public void Decrement() {
        setCount(this.getCount() - 1);
    }

//    Subtract number
    public void Decrement(int dec) {
        setCount(this.getCount() - dec);
    }

}

