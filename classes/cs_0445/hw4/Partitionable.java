// CS 0445 Spring 2021
// Partitionable interface.  Your QuickSort classes should have a
// Partitionable<T> object inside them from with the partition() 
// method will be called.

public interface Partitionable<T extends Comparable<? super T>> 
{
	public int partition(T[] a, int first, int last);
}