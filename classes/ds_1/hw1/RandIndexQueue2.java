import java.util.EmptyStackException;
import java.util.Random;

/**
 * A class implementation of a random index queue for ds_1 Assignment 1; uses empty space
 * 
 * @author Shane Riley
 * @version 1.0
 * @since 2/4/2021
 */

public class RandIndexQueue2<T> implements MyQ<T>, Indexable<T>, Shufflable {

    // Instance Variables
    private int front;      // front of queue location in array
    private int back;       // last full location in array (will be behind front if queue wraps)
    private T[] theQueue;      // queue array
    private int moves;      // used for performance evaluation
    private int increment;

    // constructor
    public RandIndexQueue2(int initialCapacity) {

        // Setting all our instance variables
        T[] theQueue = (T[]) new Object[initialCapacity];
        
        front = 0;
        back = theQueue.length - 1;
        moves = 0;
        increment = 0;
    }

    // enqueue
    public void enqueue(T newEntry) {

        // Check for full array
        if (this.size() == this.capacity()) {
            
            // Reallocate

            // Make new queue
            RandIndexQueue2<T> newQueue = new RandIndexQueue2<>(this.capacity() * 2);


            // Move the data
            while (this.size() > 0) {
                newQueue.enqueue(this.dequeue());
            }

            // Set the instance variables
            this.front = newQueue.front;
            this.back = newQueue.back;
            this.increment = newQueue.increment;
            this.moves = newQueue.moves;
            this.theQueue = newQueue.theQueue;

        }

        // Adjust the pointers
        back = (back + 1) % theQueue.length;  // Always gonna be safe
        moves++;
        increment++;

        // Put in the data
        theQueue[back] = newEntry;
    }

    // dequeue
    public T dequeue() {
        if (isEmpty()) 
            throw new EmptyQueueException();
        else {
            T theData = theQueue[front];
            // Adjust our pointers
            increment--;
            moves++;
            front = (front + 1) % theQueue.length;

            return theData;
            
        }
    }

    // capacity
    public int capacity() {
        return theQueue.length;
    }

    // size
    public int size() {
        return increment;
    }

    // isEmpty
    public boolean isEmpty() {
        return (this.size() == 0);
    }

    // Clear
    public void clear() {
        while (this.size() > 0) {
            this.dequeue();
        }
    }

    // equals
    public boolean equals(RandIndexQueue2<T> otherQueue) {

        // Check size
        if (this.size() != otherQueue.size()) return false;
        
        // Check data
        for (int i = 0; i < this.size(); i++) {
            if (!otherQueue.get(i).equals(this.get(i))) return false;
        }

        return true;
    }

    // toString

    // getFront
    public T getFront() {
        if (isEmpty()) 
            throw new EmptyQueueException();
        else
            return theQueue[front];
    }

    // get
    public T get(int index) {

        // Check bounds
        if (index >= this.size()) {
            throw new IndexOutOfBoundsException();
        }

        // Get internal index
        int internalIndex = (front + index) % theQueue.length;

        // Get the data
        return theQueue[internalIndex];
    }

    // set
    public void set(int index, T item) {

        // Check bounds
        if (index >= this.size()) {
            throw new IndexOutOfBoundsException();
        }

        // Get internal index
        int internalIndex = (front + index) % theQueue.length;

        // Set the data
        theQueue[internalIndex] = item;

    }


    // shuffle

    // getMoves

    // setMoves

    // copy constructor

}