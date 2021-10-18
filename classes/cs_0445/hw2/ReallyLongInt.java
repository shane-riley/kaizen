// CS 0445 Spring 2021
// This is a partial implementation of the ReallyLongInt class.  You need to
// complete the implementations of the remaining methods.  Also, for this class
// to work, you must complete the implementation of the LinkedListPlus class.
// See additional comments below.

public class ReallyLongInt 	extends LinkedListPlus<Integer> 
							implements Comparable<ReallyLongInt>
{
	private ReallyLongInt()
	{
		super();
	}

	// Data is stored with the LEAST significant digit first in the list.  This is
	// done by adding all digits at the front of the list, which reverses the order
	// of the original string.  Note that because the list is doubly-linked and 
	// circular, we could have just as easily put the most significant digit first.
	// You will find that for some operations you will want to access the number
	// from least significant to most significant, while in others you will want it
	// the other way around.  A doubly-linked list makes this access fairly
	// straightforward in either direction.
	public ReallyLongInt(String s)
	{
		super();
		char c;
		int digit = -1;
		// Iterate through the String, getting each character and converting it into
		// an int.  Then make an Integer and add at the front of the list.  Note that
		// the add() method (from A2LList) does not need to traverse the list since
		// it is adding in position 1.  Note also the the author's linked list
		// uses index 1 for the front of the list.
		for (int i = 0; i < s.length(); i++)
		{
			c = s.charAt(i);
			if (('0' <= c) && (c <= '9'))
			{
				digit = c - '0';
				// Do not add leading 0s
				if (!(digit == 0 && this.getLength() == 0)) 
					this.add(1, Integer.valueOf(digit));
			}
			else throw new NumberFormatException("Illegal digit " + c);
		}
		// If number is all 0s, add a single 0 to represent it
		if (digit == 0 && this.getLength() == 0)
			this.add(1, Integer.valueOf(digit));
	}

	// Copy constructor can just call super()
	public ReallyLongInt(ReallyLongInt rightOp)
	{
		super(rightOp);
	}
	
	// Constructor with a long argument.  You MUST create the ReallyLongInt
	// digits by parsing the long argument directly -- you cannot convert to a String
	// and call the constructor above.  As a hint consider the / and % operators to
	// extract digits from the long value.
	public ReallyLongInt(long X)
	{
		super();

		int digit;

		// Handle zero case
		if (X == 0) {
			this.add(0);
		} else {
			while (X > 0) {	

				// Push digit into stack
				digit = Math.floorMod(X, 10);
				this.add(digit);

				// Remove last digit using truncation
				X /= 10;
			}
		}
	}
	
	// Method to put digits of number into a String.  Note that toString()
	// has already been written for LinkedListPlus, but you need to
	// override it to show the numbers in the way they should appear.
	public String toString()
	{
		// Start with most significant digit and work backwards
		StringBuilder sb = new StringBuilder(this.getLength());
		Node thisDigit = this.firstNode.getPrevNode();

		for (int i = 0; i < this.getLength(); i++) {

			// Add digit and traverse
			sb.append(thisDigit.getData().toString());
			thisDigit = thisDigit.getPrevNode();
		}

		return sb.toString();
	}

	// See notes in the Assignment sheet for the methods below.  Be sure to
	// handle the (many) special cases.  Some of these are demonstrated in the
	// RLITest.java program.

	// Return new ReallyLongInt which is sum of current and argument
	public ReallyLongInt add(ReallyLongInt rightOp)
	{
		ReallyLongInt sum = new ReallyLongInt();

		// Zero checks
		if (this.getLength() == 0) return new ReallyLongInt(rightOp);
		if (rightOp.getLength() == 0) return new ReallyLongInt(this);

		// Start with least significant nodes
		Node tDigit = this.firstNode;
		Node rDigit = rightOp.firstNode;

		// Add the numbers
		boolean carry = false;
		for (int place = 1; place <= Math.max(this.getLength(), rightOp.getLength()); place++) 
		{
			int tValue = (this.getLength() >= place) ? tDigit.getData() : 0;  // If we are past the length the contribution is 0
			int rValue = (rightOp.getLength() >= place) ? rDigit.getData() : 0;
			int newValue = tValue + rValue + ((carry) ? 1 : 0);  // Add both sides and carry

			assert newValue < 20;

			// Does this digit need carry?
			if (newValue > 9) {
				carry = true;
				sum.add(newValue % 10);
			} else {
				carry = false;
				sum.add(newValue);
			}
			
			tDigit = tDigit.getNextNode();
			rDigit = rDigit.getNextNode();
		}

		// Handle final carry
		if (carry) sum.add(1);

		return sum;
	}
	
	// Return new ReallyLongInt which is difference of current and argument
	public ReallyLongInt subtract(ReallyLongInt rightOp)
	{
		if (this.compareTo(rightOp) == -1) throw new ArithmeticException();	
		else if (this.compareTo(rightOp) == 0) return new ReallyLongInt(0);
		
		// We know this.getLength() >= rightOp.getLength()

		// Start with least significant
		ReallyLongInt diff = new ReallyLongInt();

		// Start with least significant nodes
		Node tDigit = this.firstNode;
		Node rDigit = rightOp.firstNode;

		// Perform subtraction
		boolean carry = false;
		int lastSigDigit = 1;
		for (int place = 1; place <= this.getLength(); place++) {
			int tValue = tDigit.getData();  // Will always be valid
			int rValue = (rightOp.getLength() >= place) ? rDigit.getData() : 0;  // Goes to zero if place past end of number
			int newValue = tValue - rValue - ((carry) ? 1 : 0);  // Removes extra digit if carry

			assert newValue > -10;

			// Does this digit need carry?
			if (newValue < 0) {
				carry = true;
				newValue += 10;
			} else {
				carry = false;
			}

			// Check for nonzero place
			if (newValue != 0) lastSigDigit = place;

			diff.add(newValue);
			tDigit = tDigit.getNextNode();
			rDigit = rDigit.getNextNode();
		}

		assert diff.getLength() == this.getLength();

		// Trim leading zeros
		diff.rightShift(diff.getLength() - lastSigDigit);

		return diff;
	}

	// Return new ReallyLongInt which is product of current and argument
	public ReallyLongInt multiply(ReallyLongInt rightOp)
	{
		ReallyLongInt product = new ReallyLongInt();

		// Zero check
		ReallyLongInt zero = new ReallyLongInt(0);
		if (this.equals(zero) || rightOp.equals(zero)) return zero;  // 0

		// Start with least significant nodes
		Node tDigit = this.firstNode;
		Node rDigit = rightOp.firstNode;

		// Subproduct for handling additions
		ReallyLongInt subProduct;

		for (int tplace = 1; tplace <= this.getLength(); tplace++) {
			int tValue = tDigit.getData();
			
			for (int rplace = 1; rplace <= rightOp.getLength(); rplace++) {

				// Will always be in bounds
				int rValue = rDigit.getData();

				int numTens = (tplace - 1) + (rplace - 1);
				String subProductValue = Integer.toString(tValue * rValue)  + "0".repeat(numTens);
				subProduct = new ReallyLongInt(subProductValue);
				product = product.add(subProduct);

			// Move r forward (will cycle around for next loop)
			rDigit = rDigit.getNextNode();
			}
			
			// Move t forward
			tDigit = tDigit.getNextNode();
		}

		return product;
	}
	
	// Return -1 if current ReallyLongInt is less than rOp
	// Return 0 if current ReallyLongInt is equal to rOp
	// Return 1 if current ReallyLongInt is greater than rOp
	public int compareTo(ReallyLongInt rOp)
	{
		// Compare lengths before entries
		if (this.getLength() > rOp.getLength()) return 1;
		else if (this.getLength() < rOp.getLength()) return -1;
		else {

			// Lengths are the same
			// Start at the most significant node and work downwards
			Node thisDigit = this.firstNode.getPrevNode();
			Node rightDigit = rOp.firstNode.getPrevNode();

			for (int i = 0; i < this.getLength(); i++) {
				// Check nodal data
				if (thisDigit.getData() > rightDigit.getData()) return 1;
				else if (thisDigit.getData() < rightDigit.getData()) return -1;

				// else is equal; check next less-significant digit
				thisDigit = thisDigit.getPrevNode();
				rightDigit = rightDigit.getPrevNode();
			}
			// All digits are the same
			return 0;
		}
		
	}

	// Is current ReallyLongInt equal to rightOp?  Note that the argument
	// in this case is Object rather than ReallyLongInt.  It is written
	// this way to correctly override the equals() method defined in the
	// Object class.
	public boolean equals(Object rightOp)
	{
		// Check, then cast instance
		if (!(rightOp instanceof ReallyLongInt)) return false;
		ReallyLongInt castOp = (ReallyLongInt) rightOp;

		// Just use compareTo
		return this.compareTo(castOp) == 0;
	}
}
