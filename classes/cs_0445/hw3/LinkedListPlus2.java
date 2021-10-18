// CS 0445 Spring 2021
// Shane Riley
// LinkedListPlus2<T> class 

public class LinkedListPlus2<T> extends A2LList<T>
{
	// Default constructor simply calls super()
	public LinkedListPlus2()
	{
		super();
	}
	
	// Copy constructor
	// public LinkedListPlus2(LinkedListPlus2<T> oldList)
	// {
    //     super();
    //     if (oldList.getLength() == 0) return;
        
    //     // Make the first node
    //     this.firstNode = new Node(oldList.firstNode.data);
    //     this.numberOfEntries = oldList.numberOfEntries;

    //     Node lastNode = copyNodes(this.firstNode, oldList.firstNode, this.getLength() - 1);

    //     // Stitch beginning and end
    //     lastNode.setNextNode(this.firstNode);
    //     this.firstNode.setPrevNode(lastNode);

    // }
    // // Copy constructor rec helper
    // // Copies strings of nodes, with an int remaning
    // // Returns the left-hand final node
    // private Node copyNodes(Node currEnd, Node oldEnd, int numRemaining) {

    //     if (numRemaining == 0)
    //         return currEnd;
    //     // else

    //     // Move forward (stitch both ways)
    //     oldEnd = oldEnd.next;
    //     Node nNode = new Node(oldEnd.data);
    //     currEnd.setNextNode(nNode);
    //     nNode.setPrevNode(currEnd);

    //     currEnd = currEnd.getNextNode();
    //     return copyNodes(currEnd, oldEnd, numRemaining - 1);

    // }

    // Copy constructor (simpler implementation)
    public LinkedListPlus2(LinkedListPlus2<T> oldList) {
        super();
        if (oldList.getLength() == 0) return;
        this.copySubList(oldList.getLength(), oldList.firstNode);

    }
    private void copySubList(int numRemaining, Node oldNode) {

        // Check for base case
        if (numRemaining == 0) return;

        // Copy oldNode and add to new list
        this.add(oldNode.data);

        // Call again
        this.copySubList(numRemaining - 1, oldNode.getNextNode());
    }
    

    // toString
	public String toString()
	{
        if (this.getLength() == 0) return "";
        
        // Stub: use the recursive method
        StringBuilder b = stringRec(this.firstNode, this.getLength(), new StringBuilder());
        return b.toString();
    }
    // toString rec helper
    private StringBuilder stringRec(Node currentNode, int numRemaining, StringBuilder b) {

        // Add a digit
        b.append(currentNode.data.toString());
        b.append(" ");

        if (numRemaining != 1) {
            // Recurse
            stringRec(currentNode.getNextNode(), numRemaining - 1, b);
        }

        // Return the sb
        return b;
    }
	
	// Remove num items from the front of the list
	public void leftShift(int num)
	{
        if (num <= 0) return;
        if (num >= this.getLength()) { this.clear(); return; }

        // Find n forward from front
        Node sNode = findNodeForward(this.firstNode, num);

        // Stitch to back
        Node bNode = this.firstNode.getPrevNode();
        bNode.setNextNode(sNode);
        sNode.setPrevNode(bNode);

        // Reassign pointers
        this.firstNode = sNode;
        this.numberOfEntries -= num;
        
    }
    // Forward node finder
    private Node findNodeForward(Node n, int i) {
        if (i==0) return n;
        return findNodeBackward(n.getNextNode(), i-1);
    }

	// Remove num items from the end of the list
	public void rightShift(int num)
	{
        if (num <= 0) return;

        // Find n backward from back
        Node sNode = findNodeBackward(this.firstNode.prev, num);

        // Stitch to front
        sNode.setNextNode(this.firstNode);
        this.firstNode.setPrevNode(sNode);

        // Reassign pointers
        this.numberOfEntries -= num;
    }
    // Backward node finder
    private Node findNodeBackward(Node n, int i) {
        if (i==0) return n;
        return findNodeBackward(n.getPrevNode(), i-1);
    }

	// Rotate to the left num locations in the list.  No Nodes
	// should be created or destroyed.
	public void leftRotate(int num)
	{
        if (num < 0) { rightRotate(-1 * num); return; }

        // Find n nodes forward from front
        this.firstNode = findNodeForward(this.firstNode, num);
	}

	// Rotate to the right num locations in the list.  No Nodes
	// should be created or destroyed.
	public void rightRotate(int num)
	{
        if (num < 0) { leftRotate(-1 * num); return; }

        // Find n nodes backward from front
        this.firstNode = findNodeBackward(this.firstNode, num);
	}	
}
