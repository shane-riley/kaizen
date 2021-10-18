// CS 0445 Spring 2021
// LinkedListPlus<T> class partial implementation

// See the commented methods below.  You must complete this class by
// filling in the method bodies for the remaining methods.  Note that you
// may NOT add any new instance variables, but you may use method variables
// as needed.

public class LinkedListPlus<T> extends A2LList<T>
{
	// Default constructor simply calls super()
	public LinkedListPlus()
	{
		super();
	}
	
	// Copy constructor.  This is a "deepish" copy so it will make new
	// Node objects for all of the nodes in the old list.  However, it
	// is not totally deep since it does NOT make copies of the objects
	// within the Nodes -- rather it just copies the references.  The
	// idea of this method is as follows:  If oldList has at least one
	// Node in it, create the first Node for the new list, then iterate
	// through the old list, appending a new Node in the new list for each
	// Node in the old List.  At the end, link the Nodes around to make sure
	// that the list is circular.
	public LinkedListPlus(LinkedListPlus<T> oldList)
	{
		super();
		if (oldList.getLength() > 0)
		{
			// Special case for first Node since we need to set the
			// firstNode instance variable.
			Node temp = oldList.firstNode;
			Node newNode = new Node(temp.data);
			firstNode = newNode;
			
			// Now we traverse the old list, appending a new Node with
			// the correct data to the end of the new list for each Node
			// in the old list.  Note how the loop is done and how the
			// Nodes are linked.
			Node currNode = firstNode;
			temp = temp.next;
			int count = 1;
			while (count < oldList.getLength())
			{
				newNode = new Node(temp.data);
				currNode.next = newNode;
				newNode.prev = currNode;
				temp = temp.next;
				currNode = currNode.next;
				count++;
			}
			currNode.next = firstNode;  // currNode is now at the end of the list.
			firstNode.prev = currNode;	// link to make the list circular
			numberOfEntries = oldList.numberOfEntries;
		}			
	}

	// Make a StringBuilder then traverse the nodes of the list, appending the
	// toString() of the data for each node to the end of the StringBuilder.
	// Finally, return the StringBuilder as a String.  Note that since the list
	// is circular, we cannot look for null.  Rather we must count the Nodes as
	// we progress down the list.
	public String toString()
	{
		StringBuilder b = new StringBuilder();
		Node curr = firstNode;
		int i = 0;
		while (i < this.getLength())
		{
			b.append(curr.data.toString());
			b.append(" ");
			curr = curr.next;
			i++;
		}
		return b.toString();
	}
	
	// Remove num items from the front of the list
	public void leftShift(int num)
	{
		if (this.isEmpty() || num <= 0) return;  // Do nothing if empty or num <= 0
		else if (num >= this.getLength()) this.clear(); // All nodes dropped
		else {
			// Get back node
			Node backNode = this.firstNode.getPrevNode();

			// Find new first node
			Node currentNode = this.firstNode;
			for (int i = 0; i < num; i++) {
				currentNode = currentNode.getNextNode();
			}

			// Set new first node
			this.firstNode = currentNode;

			// Stitch new front and back nodes (ones in between are dropped)
			this.firstNode.setPrevNode(backNode);
			backNode.setNextNode(this.firstNode);
		}
		this.numberOfEntries -= num;
	}

	// Remove num items from the end of the list
	public void rightShift(int num)
	{
		if (this.isEmpty() || num <= 0) return;  // Do nothing if empty or num <= 0
		else if (num >= this.getLength()) this.clear(); // All nodes dropped
		else {
			// Get back node
			Node backNode = this.firstNode.getPrevNode();

			// Find new back node
			Node currentNode = backNode;
			for (int i = 0; i < num; i++) {
				currentNode = currentNode.getPrevNode();
			}

			// Stitch current and front nodes (ones in between are dropped)
			currentNode.setNextNode(this.firstNode);
			this.firstNode.setPrevNode(currentNode);
		}
		this.numberOfEntries -= num;
	}

	// Rotate to the left num locations in the list.  No Nodes
	// should be created or destroyed.
	public void leftRotate(int num)
	{
		if (this.isEmpty()) return;  // Do nothing if empty

		// Find the index of the new first node (should handle negatives using mod)
		int numToShift = Math.floorMod(num, this.getLength());  // Using floorMod will ensure positive index within bounds

		// The stock getNodeAt method is private in A2List, so we will traverse using numToShift (similar implementation)
		Node currentNode = this.firstNode;
		for (int i = 0; i < numToShift; i++) {
			currentNode = currentNode.getNextNode();
		}

		// Set node
		this.firstNode = currentNode;
	}

	// Rotate to the right num locations in the list.  No Nodes
	// should be created or destroyed.
	public void rightRotate(int num)
	{
		if (this.isEmpty()) return;  // Do nothing if empty

		// Find the index of the new first node (should handle negatives using mod)
		int numToShift = Math.floorMod(num, this.getLength());  // Using floorMod will ensure positive index within bounds

		// The stock getNodeAt method is private in A2List, so we will traverse using numToShift (similar implementation)
		Node currentNode = this.firstNode;
		for (int i = 0; i < numToShift; i++) {
			currentNode = currentNode.getPrevNode();
		}

		// Set node
		this.firstNode = currentNode;
	}	
}
