import java.util.Random;

/**
 * A class implementation of a random index queue for ds_1 Assignment 1; uses empty space
 * 
 * @author Shane Riley
 * @version 1.0
 * @since 2/4/2021
 */

public class RandIndexQueue<T> implements MyQ<T>, Indexable<T>, Shufflable {

    // Instance Variables
    private int front;      // front of queue location in array
    private int back;       // last full location in array (will be behind front if queue wraps)
    private T[] queue;      // queue array
    private int moves;      // used for performance evaluation

    // When the back pointer is one behind the front pointer, the queue is empty
    // When the back pointer is two behind the front pointer, the queue is full

    // Constructor
    @SuppressWarnings("unchecked")
    public RandIndexQueue(int inputSize) {
        // Create queue array
        queue = (T[]) new Object[inputSize + 1];

        // Set pointers
        front = 0;
        back = queue.length - 1;

        // Set moves
        moves = 0;
    }

    public RandIndexQueue() {
        RandIndexQueue(5);
    }

    // Copy Constructor
    @SuppressWarnings("unchecked")
    public RandIndexQueue(RandIndexQueue old) {
        
        // Simple copy of queue
        queue = (T[]) new Object[old.capacity() + 1];

        for (int i = 0; i < queue.length; i++) {
            queue[i] = (T) old.queue[i];
        }

        // Copy points
        front = old.front;
        back = old.back;
        moves = old.moves;
    }

    // Equals
    @SuppressWarnings("unchecked")
    public boolean equals(Object otherObject) {
        if (!(otherObject instanceof RandIndexQueue))    return false;
        RandIndexQueue<T> otherQueue = (RandIndexQueue<T>) otherObject;

        // Check size
        if (otherQueue.size() != this.size())   return false;

        // Check items
        for (int i=0; i < this.size(); i++) {
            if (!this.get(i).equals(otherQueue.get(i))) return false;
        }

        return true;
    }

    // toString
    public String toString() {
        StringBuilder sb = new StringBuilder("Contents ");

        for (int i = 0; i < this.size(); i++) {
            sb.append(this.get(i).toString());
            sb.append(" ");
        }
        
        return sb.toString();
    }

    // Enqueue
    
    public void enqueue(T newEntry) {
        // Check for full

        if (this.isFull()) this.reallocate();

        back = (back+1) % queue.length;
        queue[back] = newEntry;
        moves++;
    }

    // Internal reallocate
    @SuppressWarnings("unchecked")
    private void reallocate() {
        // Copy to new queue in queue order
        int oldCapacity = this.capacity();
        T[] newQueue = (T[]) new Object[((queue.length - 1) * 2) + 1];  // minus one, double, plus one
        int oldIndex;
        for (int newIndex=0; newIndex < queue.length; newIndex++) {
            oldIndex = (newIndex + front) % queue.length;
            newQueue[newIndex] = queue[oldIndex];
        }

        // Reset pointers
        front = 0;
        back = oldCapacity - 1;  // Old length

        // Replace array
        queue = newQueue;
    }

    // Dequeue
    public T dequeue() {
        // Check for empty queue
        if (this.isEmpty()) {
            throw new EmptyQueueException();
        }
        // Else

        // Get entry
        T grabbedEntry = queue[front];

        // Move front pointer forward to no longer cover old entry
        front = (front+1) % queue.length;

        moves++;
        return grabbedEntry;
    }

    // getFront
    public T getFront() {
        // Check for empty queue
        if (this.isEmpty()) {
            throw new EmptyQueueException();
        }
        // Else
        // Return front entry
        return queue[front];
    }

    // isEmpty
    public boolean isEmpty() {
        // If size is 0
        return (this.size() == 0);
    }

    // isFull
    public boolean isFull() {
        // If size is capacity
        return (this.size() == this.capacity());
    }

    // clear
    @SuppressWarnings("unchecked")
    public void clear() {
        // Reinstantiate queue with old size
        queue = (T[]) new Object[queue.length];

        // Reset pointers
        front = 0;
        back = queue.length - 1;

        // Reset moves
        moves = 0;
    }

    // size
    public int size() {
        // Handles all cases
        int testValue = (back - front + 1) % queue.length;
        return (testValue < 0) ? queue.length - 1 + testValue : testValue;
    }

    // capacity
    public int capacity() {
        // The array length is the current capacity of the queue
        return queue.length - 1;
    }

    // getMoves
    public int getMoves() {
        // Return primitive instance variable
        return moves;
    }

    // setMoves
    public void setMoves(int newMoves) {
        // Unchecked set of primitive moves
        moves = newMoves;
    }

    // get
    public T get(int index) {
        // Return object based on 0 as logical front
        // Shallow return

        if (index + 1 > this.size()) {
            throw new IndexOutOfBoundsException();
        }
        // Else

        int internalIndex = (index+front) % queue.length;
        return queue[internalIndex];
    }

    // set
    public void set(int index, T item) {
        // Set object based on 0 as logical front
        // Shallow set

        if (index + 1 > this.size()) {
            throw new IndexOutOfBoundsException();
        }
        // Else

        int internalIndex = (index+front) % queue.length;
        queue[internalIndex] = item;
    }

    // shuffle
    public void shuffle() {

        Random rand = new Random();

        for (int i = 0; i < this.size(); i++) {
            // Swap for another entry within the queue
            int toSwap = rand.nextInt(this.size());

            // Swap the entries
            T temp = this.get(i);
            this.set(i, this.get(toSwap));
            this.set(toSwap, temp);
        }
    }
}
