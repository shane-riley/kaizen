// ds_1 Spring 2021
// Shane Riley
// ReallyLongInt2 class 

public class ReallyLongInt2 	extends LinkedListPlus2<Integer> 
							implements Comparable<ReallyLongInt2>
{
	private ReallyLongInt2()
	{
		super();
	}

	// Data is stored with the LEAST significant digit first in the list.
	public ReallyLongInt2(String s)
	{
		super();
		this.stringBuildRec(s, 0);
	}
	// Internal build string
	private void stringBuildRec(String s, int i) {

		if (i >= s.length()) return;

		// Add the digit
		int digit;
		char c = s.charAt(i);
		if (('0' <= c) && (c <= '9'))
		{
			digit = c - '0';
			// Do not add leading 0s
			if (!(digit == 0 && this.getLength() == 0)) 
				this.add(1, Integer.valueOf(digit));
		}
		else throw new NumberFormatException("Illegal digit " + c);

		this.stringBuildRec(s, i+1);
	}

	// Copy constructor can just call super()
	public ReallyLongInt2(ReallyLongInt2 rightOp)
	{
		super(rightOp);
	}
	
	// Constructor with a long argument.
	public ReallyLongInt2(long X)
	{
		super();
		this.longBuildRec(X);
	}
	// Internal build long
	private void longBuildRec(long X) {
		if (X==0) return;
		this.add((int) X % 10);
		longBuildRec(X/10);
		return;
	}
	
	// toString
	public String toString()
	{
        if (this.getLength() == 0) return "0";
        
        // Stub: use the recursive method
		StringBuilder b = stringRec(this.firstNode, this.getLength(), new StringBuilder());
        return b.reverse().toString();
    }
    // toString rec helper
    private StringBuilder stringRec(Node currentNode, int numRemaining, StringBuilder b) {

        // Add a digit
        b.append(currentNode.getData().toString());

        if (numRemaining != 1) {
            // Recurse
            stringRec(currentNode.getNextNode(), numRemaining - 1, b);
        }

        // Return the sb
        return b;
    }

	// Return new ReallyLongInt2 which is sum of current and argument
	public ReallyLongInt2 add(ReallyLongInt2 rightOp)
	{
		// Zeros check
		if (rightOp.getLength() == 0) return new ReallyLongInt2(this);
		if (this.getLength() == 0) return new ReallyLongInt2(rightOp);

		// Both are nonzero
		return recAdd(new ReallyLongInt2(), this.firstNode, rightOp.firstNode, 1, false, this.getLength(), rightOp.getLength());

	}
	private ReallyLongInt2 recAdd(ReallyLongInt2 subSum, Node tNode, Node rNode, int place, boolean carry, int tLength, int rLength) {
		if (place > Math.max(tLength,rLength) && !carry) return subSum;
		int newDigitValue = (
				((place <= tLength) ? tNode.getData() : 0)
			+	((place <= rLength) ? rNode.getData() : 0)
			+	((carry)			? 1 : 0)
		);

		if (newDigitValue > 9) {
			carry = true;
			newDigitValue -= 10;
		} else { carry = false; };

		subSum.add(newDigitValue);

		return recAdd(subSum, tNode.getNextNode(), rNode.getNextNode(), place + 1, carry, tLength, rLength);
	}
	
	// Return new ReallyLongInt2 which is difference of current and argument
	public ReallyLongInt2 subtract(ReallyLongInt2 rightOp)
	{
		// Zeros check
		if (rightOp.getLength() == 0) return new ReallyLongInt2(this);
		if (this.getLength() == 0) return new ReallyLongInt2(rightOp);

		if (this.compareTo(rightOp) == -1) throw new ArithmeticException();
		if (this.compareTo(rightOp) == 0) return new ReallyLongInt2();

		// Both are nonzero
		ReallyLongInt2 diff = recSub(new ReallyLongInt2(), this.firstNode, rightOp.firstNode, 1, false, this.getLength(), rightOp.getLength());
		diff.trimLeadingZeros();
		return diff;

	}
	private ReallyLongInt2 recSub(ReallyLongInt2 subDiff, Node tNode, Node rNode, int place, boolean carry, int tLength, int rLength) {
		if (place > Math.max(tLength,rLength)) return subDiff;

		int newDigitValue = (
				tNode.getData()
			-	((place <= rLength) ? rNode.getData() : 0)
			-	((carry)			? 1 : 0)
		);

		if (newDigitValue < 0) {
			carry = true;
			newDigitValue += 10;
		} else { carry = false; };

		subDiff.add(newDigitValue);

		return recSub(subDiff, tNode.getNextNode(), rNode.getNextNode(), place + 1, carry, tLength, rLength);
	}

	private void trimLeadingZeros() {
		int nLeading = this.findNumLeadingZeros(this.firstNode.getPrevNode(), 0);
		this.rightShift(nLeading);
	}
	private int findNumLeadingZeros(Node n, int i) {
		if (n.getData() != 0) return i;
		if (i > this.getLength()) return this.getLength() - 1;
		return findNumLeadingZeros(n.getPrevNode(), i + 1);
	}

	// Return new ReallyLongInt2 which is product of current and argument
	public ReallyLongInt2 multiply(ReallyLongInt2 rightOp)
	{
		// Zero checks
		if (rightOp.getLength() == 0) return new ReallyLongInt2();
		if (this.getLength() == 0) return new ReallyLongInt2();

		return multNumIncLeft(this.firstNode, rightOp, 1, this.getLength());
	}

	private ReallyLongInt2 multNumIncLeft(Node tNode, ReallyLongInt2 rightOp, int tplace, int tLength) {
		if (tplace > tLength) return new ReallyLongInt2();

		ReallyLongInt2 current = multDigitIncRight(tNode, rightOp.firstNode, tplace, 1, rightOp.getLength());
		ReallyLongInt2 afterThis = multNumIncLeft(tNode.getNextNode(), rightOp, tplace + 1, tLength);
		ReallyLongInt2 both = current.add(afterThis);
		return both;
	}

	private ReallyLongInt2 multDigitIncRight(Node tNode, Node rNode, int tplace, int rplace, int rLength) {
		if (rplace > rLength) return new ReallyLongInt2();
		int digitProduct = tNode.getData() * rNode.getData();
		String prodString = String.valueOf(digitProduct) + "0".repeat(tplace + rplace - 2);
		ReallyLongInt2 current = new ReallyLongInt2(prodString);
		ReallyLongInt2 afterThis = multDigitIncRight(tNode, rNode.getNextNode(), tplace, rplace + 1, rLength);
		return current.add(afterThis);
	}
	
	// Return -1 if current ReallyLongInt2 is less than rOp
	// Return 0 if current ReallyLongInt2 is equal to rOp
	// Return 1 if current ReallyLongInt2 is greater than rOp
	public int compareTo(ReallyLongInt2 rOp)
	{
		// Do a length comparison (precondition that there are no leading zeros)
		if (this.getLength() > rOp.getLength()) return 1;
		if (rOp.getLength() > this.getLength()) return -1;

		// else
		return compareNodes(this.firstNode.getPrevNode(), rOp.firstNode.getPrevNode(), this.getLength());
	}
	private int compareNodes(Node tNode, Node rNode, int n) {
		// Check base
		if (n==0) return 0;

		// Check the values
		int tValue = tNode.getData();
		int rValue = rNode.getData();
		if (tValue > rValue) return 1;
		if (rValue > tValue) return -1;

		// Recurse
		return compareNodes(tNode.getPrevNode(), rNode.getPrevNode(), n-1);
	}

	// Is current ReallyLongInt2 equal to rightOp?  Note that the argument
	// in this case is Object rather than ReallyLongInt2.  It is written
	// this way to correctly override the equals() method defined in the
	// Object class.
	public boolean equals(Object rightOp)
	{
		// Check, then cast instance
		if (!(rightOp instanceof ReallyLongInt2)) return false;
		ReallyLongInt2 castOp = (ReallyLongInt2) rightOp;

		// Just use compareTo
		return this.compareTo(castOp) == 0;
	}
}
