// ds_1 Spring 2021
// Shane Riley
// A2List class 
// Modified to be recursive

/**
   A linked implementation of the ADT list.
   @author Frank M. Carrano
*/
public class A2LList<T> 
{
	protected Node firstNode;     // reference to first node
	protected int numberOfEntries; 

	public A2LList()
	{
		clear();
	} // end default constructor
	
	public final void clear() // note the final method
	{
		firstNode = null;
		numberOfEntries = 0;
	} // end clear
	
	public int getLength()
	{
		return numberOfEntries;
	}
	
	public void add(T newEntry)
	{
   		Node newNode = new Node(newEntry);
		
		// Special case for empty list -- node points to itself
		// in both directions.
   		if (isEmpty())
   		{
      		firstNode = newNode;
      		firstNode.setPrevNode(firstNode);
      		firstNode.setNextNode(firstNode);
      	}
   		else	// add to end of non-empty list.  Note that because
				// it is doubly-linked and circular, we can get to
				// the end Node easily.
   		{
      		Node lastNode = firstNode.getPrevNode();
      		lastNode.setNextNode(newNode); 
      		newNode.setPrevNode(lastNode);
      		newNode.setNextNode(firstNode);
      		firstNode.setPrevNode(newNode);
   		} // end if	
   
   		numberOfEntries++;
	}  // end add
	
	// For this add() we must traverse to the correct location before
	// adding the node.  
	public boolean add(int newPosition, T newEntry)	                                                 
	{
   		boolean isSuccessful = true;

   		if ((newPosition >= 1) && (newPosition <= numberOfEntries + 1)) 
   		{	
      		Node newNode = new Node(newEntry);

			// Special case for empty list -- node points to itself
			// in both directions.
   			if (isEmpty())
   			{
      			firstNode = newNode;
      			firstNode.setPrevNode(firstNode);
      			firstNode.setNextNode(firstNode);
      		}
      		else if (newPosition == 1)   // Special case for adding at front
      		{
      			Node lastNode = firstNode.getPrevNode();
         		newNode.setNextNode(firstNode);
         		firstNode.setPrevNode(newNode);
         		newNode.setPrevNode(lastNode);
         		lastNode.setNextNode(newNode);				
         		firstNode = newNode;
      		}
      		else	// Adding in the middle							
      		{                                
         		Node nodeBefore = getNodeAt(newPosition - 1);
         		Node nodeAfter = nodeBefore.getNextNode();
         		newNode.setNextNode(nodeAfter);
         		nodeBefore.setNextNode(newNode);
         		nodeAfter.setPrevNode(newNode);
         		newNode.setPrevNode(nodeBefore);
      		} // end if	
   
      		numberOfEntries++;
   		}
   		else
      		isSuccessful = false;
      
   		return isSuccessful;
	} // end add
	
	public boolean isEmpty()
	{
   		boolean result;
      
   		if (numberOfEntries == 0) // or getLength() == 0
   		{
      		result = true;
   		}
   		else
   		{
      		result = false;
   		} // end if
      
   		return result;
	} // end isEmpty
  
	public T remove(int givenPosition)
	{
   		T result = null;                           // return value

   		if ((givenPosition >= 1) && (givenPosition <= numberOfEntries))
   		{
			if (numberOfEntries == 1)	// case 1: remove only entry -- this is
			{							// special because of the circular list.
				result = firstNode.getData();
				firstNode = null;
			}	
      		else if (givenPosition == 1)             // case 2: remove first entry
      		{
         		result = firstNode.getData();        // save entry to be removed 
         		Node lastNode = firstNode.getPrevNode();
         		firstNode = firstNode.getNextNode(); // move firstNode down
         		lastNode.setNextNode(firstNode);	//  reset neighbors
         		firstNode.setPrevNode(lastNode);
      		}
      		else                                    // case 3: not first entry
      		{  
         		Node nodeBefore = getNodeAt(givenPosition - 1);
         		Node nodeToRemove = nodeBefore.getNextNode();
         		Node nodeAfter = nodeToRemove.getNextNode();
         		nodeBefore.setNextNode(nodeAfter);
         		nodeAfter.setPrevNode(nodeBefore);  
         		result = nodeToRemove.getData();    // save entry to be removed
      		} // end if

      		numberOfEntries--;
   		} // end if

   		return result;                            // return removed entry, or 
                                             // null if operation fails
	} // end remove

	public boolean replace(int givenPosition, T newEntry)
	{
   		boolean isSuccessful = true;

   		if ((givenPosition >= 1) && (givenPosition <= numberOfEntries))
   		{   
      		assert !isEmpty();

      		Node desiredNode = getNodeAt(givenPosition);
      		desiredNode.setData(newEntry);
   		}    
   		else
      		isSuccessful = false;
      
   		return isSuccessful;
	} // end replace

// This method is intentionally commented out and you may not use it in your
// LinkedListPlus or ReallyLongInt classes.  However, you can uncomment it
// during development / for testing as long as the comments are back in your
// final submitted version.
/*
	public T getEntry(int givenPosition)
	{
   		T result = null;  // result to return
   
   		if ((givenPosition >= 1) && (givenPosition <= numberOfEntries))
   		{
      		result = getNodeAt(givenPosition).getData();
   		} // end if
   
   		return result;
	} // end getEntry
*/
	
	public boolean contains(T anEntry)
	{
   		return checkNodeValues(this.firstNode, 1, anEntry);
	} // end contains
	private boolean checkNodeValues(Node n, int i, T entry) {
		if (i > this.getLength()) return false;
		if (n.getData().equals(entry)) return true;
		return checkNodeValues(n.getNextNode(), i+1, entry);
	}

   // Returns a reference to the node at a given position.
   // Precondition: List is not empty;
   //               1 <= givenPosition <= numberOfEntries	   
	private Node getNodeAt(int givenPosition)
	{
		assert !isEmpty() && (1 <= givenPosition) && (givenPosition <= numberOfEntries);
		Node currentNode = firstNode;
		
      // traverse the list to locate the desired node
		currentNode = findNodeForward(currentNode, givenPosition - 1);
		
		assert currentNode != null;
      
		return currentNode;
	} // end getNodeAt
	private Node findNodeForward(Node n, int i) {
		if (i==0) return n;
		return findNodeForward(n.getNextNode(), i-1);
	}

	// Note that this class is protected so you can access it directly from
	// your LinkedListPlus and ReallyLongInt classes.  However, in case you
	// prefer using accessors and mutators, those are also provided here.
   protected class Node
   {
      protected T data; 	// entry in list
      protected Node next; 	// link to next node
      protected Node prev;  // link to prev node
      
      protected Node(T dataPortion)
      {
         this(dataPortion, null, null);
      } // end constructor
      
      protected Node(T dataPortion, Node nextNode, Node prevNode)
      {
         data = dataPortion;
         next = nextNode;
         prev = prevNode;
      } // end constructor
      
      protected T getData()
      {
         return data;
      } // end getData
      
      protected void setData(T newData)
      {
         data = newData;
      } // end setData
      
      protected Node getNextNode()
      {
         return next;
      } // end getNextNode
      
      protected void setNextNode(Node nextNode)
      {
         next = nextNode;
      } // end setNextNode
      
      protected Node getPrevNode()
      {
      	return prev;
      }
      
      protected void setPrevNode(Node prevNode)
      {
      	prev = prevNode;
      }
   } // end Node

//    Main method for testing
	public static void main (String [] args)
	{
		// Testing constructor
		A2LList<Integer> L1 = new A2LList<Integer>();
		for (int i = 0; i < 8; i++)
		{
			L1.add(Integer.valueOf(i));
		}
		System.out.println("L1: " + L1.toString());
		System.out.println("(is 0 1 2 3 4 5 6 7)");
		System.out.println("L1 contains 9: " + L1.contains(9));
		System.out.println("L1 contains 7: " + L1.contains(7));
		System.out.println("L1 contains 1: " + L1.contains(1));
		System.out.println("Node data at index 5: " + L1.getNodeAt(5).getData());
	}
} // end A2LList