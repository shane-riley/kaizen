/**
 * HeftyInteger for CS1501 Project 5
 * @author	Dr. Farnan
 */
package cs1501_p5;
public class HeftyInteger {

	private final byte[] ONE = {(byte) 1};

	private byte[] val;

	/**
	 * Construct the HeftyInteger from a given byte array
	 * @param b the byte array that this HeftyInteger should represent
	 */
	public HeftyInteger(byte[] b) {
		val = b;
	}

	/**
	 * Return this HeftyInteger's val
	 * @return val
	 */
	public byte[] getVal() {
		return val;
	}

	/**
	 * Return the number of bytes in val
	 * @return length of the val byte array
	 */
	public int length() {
		return val.length;
	}

	/**
	 * Add a new byte as the most significant in this
	 * @param extension the byte to place as most significant
	 */
	public void extend(byte extension) {
		byte[] newv = new byte[val.length + 1];
		newv[0] = extension;
		for (int i = 0; i < val.length; i++) {
			newv[i + 1] = val[i];
		}
		val = newv;
	}

	/**
	 * If this is negative, most significant bit will be 1 meaning most
	 * significant byte will be a negative signed number
	 * @return true if this is negative, false if positive
	 */
	public boolean isNegative() {
		return (val[0] < 0);
	}

	/**
	 * Computes the sum of this and other
	 * @param other the other HeftyInteger to sum with this
	 */
	public HeftyInteger add(HeftyInteger other) {
		byte[] a, b;
		// If operands are of different sizes, put larger first ...
		if (val.length < other.length()) {
			a = other.getVal();
			b = val;
		}
		else {
			a = val;
			b = other.getVal();
		}

		// ... and normalize size for convenience
		if (b.length < a.length) {
			int diff = a.length - b.length;

			byte pad = (byte) 0;
			if (b[0] < 0) {
				pad = (byte) 0xFF;
			}

			byte[] newb = new byte[a.length];
			for (int i = 0; i < diff; i++) {
				newb[i] = pad;
			}

			for (int i = 0; i < b.length; i++) {
				newb[i + diff] = b[i];
			}

			b = newb;
		}

		// Actually compute the add
		int carry = 0;
		byte[] res = new byte[a.length];
		for (int i = a.length - 1; i >= 0; i--) {
			// Be sure to bitmask so that cast of negative bytes does not
			//  introduce spurious 1 bits into result of cast
			carry = ((int) a[i] & 0xFF) + ((int) b[i] & 0xFF) + carry;

			// Assign to next byte
			res[i] = (byte) (carry & 0xFF);

			// Carry remainder over to next byte (always want to shift in 0s)
			carry = carry >>> 8;
		}

		HeftyInteger res_li = new HeftyInteger(res);

		// If both operands are positive, magnitude could increase as a result
		//  of addition
		if (!this.isNegative() && !other.isNegative()) {
			// If we have either a leftover carry value or we used the last
			//  bit in the most significant byte, we need to extend the result
			if (res_li.isNegative()) {
				res_li.extend((byte) carry);
			}
		}
		// Magnitude could also increase if both operands are negative
		else if (this.isNegative() && other.isNegative()) {
			if (!res_li.isNegative()) {
				res_li.extend((byte) 0xFF);
			}
		}

		// Note that result will always be the same size as biggest input
		//  (e.g., -127 + 128 will use 2 bytes to store the result value 1)
		return res_li;
	}

	/**
	 * Negate val using two's complement representation
	 * @return negation of this
	 */
	public HeftyInteger negate() {
		byte[] neg = new byte[val.length];
		int offset = 0;

		// Check to ensure we can represent negation in same length
		//  (e.g., -128 can be represented in 8 bits using two's
		//  complement, +128 requires 9)
		if (val[0] == (byte) 0x80) { // 0x80 is 10000000
			boolean needs_ex = true;
			for (int i = 1; i < val.length; i++) {
				if (val[i] != (byte) 0) {
					needs_ex = false;
					break;
				}
			}
			// if first byte is 0x80 and all others are 0, must extend
			if (needs_ex) {
				neg = new byte[val.length + 1];
				neg[0] = (byte) 0;
				offset = 1;
			}
		}

		// flip all bits
		for (int i  = 0; i < val.length; i++) {
			neg[i + offset] = (byte) ~val[i];
		}

		HeftyInteger neg_li = new HeftyInteger(neg);

		// add 1 to complete two's complement negation
		return neg_li.add(new HeftyInteger(ONE));
	}

	/**
	 * Implement subtraction as simply negation and addition
	 * @param other HeftyInteger to subtract from this
	 * @return difference of this and other
	 */
	public HeftyInteger subtract(HeftyInteger other) {
		return this.add(other.negate());
	}

	/**
	 * Compute the product of this and other
	 * @param other HeftyInteger to multiply by this
	 * @return product of this and other
	 */
	public HeftyInteger multiply(HeftyInteger other) {


		// If this is negative, we cheat
		if (this.isNegative()) {
			this.val = this.negate().getVal();
			other = other.negate();
		}

		// Lets loop through the bits of this to confirm mult and leftshift other
		byte[] temp = {0};
		HeftyInteger result = new HeftyInteger(temp);

		// Lets cache the other's current bitshift to not repeat work
		int cachedbitLoc = 0;
		HeftyInteger cacheOther = new HeftyInteger(other.getVal());

		// Loop through this
		// little-endian byteloop
		for (int nB = this.length() - 1; nB >= 0 ; nB--) {

			// little-endian bitloop
			for (int nb = 0; nb < 8; nb++) {

				// Determine total little-endian bit location (complement of byte index)
				int bitLoc = ((this.length() - nB - 1) * 8) + nb;

				// Perform a shift add iff bit is positive
				if (1 == getBit(this.getVal(), nB, nb)) {
					cacheOther = cacheOther.leftShift(bitLoc - cachedbitLoc);
					cachedbitLoc = bitLoc;
					result = result.add(cacheOther);
				}
			}
		}
		return result;
	}

	private HeftyInteger leftShift(int n) {
		
		// We are gonna iterate through bits because i'm not clever enough to do anything else
		
		// Get sign for later
		boolean isNeg = this.isNegative();

		// Add extra bytes
		int numExtraBits = this.numExtraBits();
		int numSigBits = (this.length() * 8) - numExtraBits;
		int bitsToAdd = Math.max(0, n - numExtraBits);
		int bytesToAdd = 0;
		if (bitsToAdd > 0) {
			bytesToAdd = (bitsToAdd / 8) + 1;
		}
		byte[] newVal = new byte[this.length() + bytesToAdd];

		// Mapping
		// Bigendian byteloop
		for (int nB = 0; nB < newVal.length; nB++) {
			// bitloop
			for (int nb = 0; nb < 8; nb++) {

				// Determine total little-endian bit location (complement of byte index)
				int bitLoc = ((newVal.length - nB - 1) * 8) + nb;

				// bitLoc < n => 				is zero
				// bitLoc < n + numSigBits => 	map
				// bitLoc >= n + numSigBits =>	is signbit

				if (bitLoc < n) {
					setBit(newVal, nB, nb, 0);
				} else if (bitLoc < (n + numSigBits)) {
					int bitLocOld = bitLoc - n;
					int nbOld = bitLocOld % 8;
					int nBOld = this.length() - (bitLocOld / 8) - 1;
					int bit = getBit(this.getVal(), nBOld, nbOld);
					setBit(newVal, nB, nb, bit);
				} else {
					setBit(newVal, nB, nb, (isNeg ? 1 : 0));
				}
			}
		}
		
		HeftyInteger result = new HeftyInteger(newVal);
		return result.trim();
	}

	// Trim in place
	private HeftyInteger trim() {
		
		// Big endian
		int bytesToDrop = (this.numExtraBits() / 8);
		if (bytesToDrop > 0) {
			// Make a new val array and map
			byte[] newVal = new byte[this.length() - bytesToDrop];
			for (int i = 0; i < newVal.length; i++) {
				newVal[i] = this.getVal()[i + bytesToDrop];
			}
			this.val = newVal;
		}
		return this;
	}

	// Get num extra bits
	private int numExtraBits() {

		// Get sign
		boolean isNeg = this.isNegative();

		int numBits = 0;

		// Bigendian byteloop
		for (int nB = 0; nB < this.length(); nB++) {
			// Bigendian bitloop
			for (int nb = 7; nb >= 0; nb--) {

				if (getBit(this.getVal(), nB, nb) == 1 ^ isNeg) {
					// Found offcolor bit
					return --numBits;
				}
				numBits++;
			}
		}
		return --numBits;
	}

	// total byte big-endian bitget
	private int getBit(byte[] bytes, int nB, int nb) {
		return ((bytes[nB] >> nb) & 1);
	}

	// total byte big-endian bitset
	private void setBit(byte[] bytes, int nB, int nb, int val) {
		bytes[nB] ^= (-val ^ bytes[nB]) & (1 << nb);
	}

	/**
	 * Run the extended Euclidean algorithm on this and other
	 * @param other another HeftyInteger
	 * @return an array structured as follows:
	 *   0:  the GCD of this and other
	 *   1:  a valid x value
	 *   2:  a valid y value
	 * such that this * x + other * y == GCD in index 0
	 */
	public HeftyInteger[] XGCD(HeftyInteger other) {
	
		// Get the gcd
		HeftyInteger a, b, div, rem, s, t, sback, tback, tnext, snext;
		HeftyInteger gcd;
		byte[] temp = {0};
		s = new HeftyInteger(temp);
		t = new HeftyInteger(ONE);
		sback = new HeftyInteger(ONE);
		tback = new HeftyInteger(temp);
		div = new HeftyInteger(ONE);
		s = new HeftyInteger(temp);
		t = new HeftyInteger(ONE);
		sback = new HeftyInteger(ONE);
		tback = new HeftyInteger(temp);

		// set a and b (a is always greater)
		boolean flipFlag = (this.compareTo(other) == 1);
		if (flipFlag)  {
			a = new HeftyInteger(this.getVal());
			b = new HeftyInteger(other.getVal());
			
		} else {
			a = new HeftyInteger(other.getVal());
			b = new HeftyInteger(this.getVal());
		}
		
		// Starting gcd
		gcd = b;
		rem = sback;
		while (!rem.isZero()) {

			// Set gcd
			gcd = rem;

			// Get div and rem
			div = a.divide(b);
			rem = a.subtract(b.multiply(div));

			// Get s and t
			snext = sback.subtract(div.multiply(s));
			tnext = tback.subtract(div.multiply(t));
			sback = s;
			tback = t;
			s = snext;
			t = tnext;

			// Set a and b
			a = b;
			b = rem;
			
		}

		// Answer is gcd, sback and tback
		if (flipFlag) {
			HeftyInteger[] hf = {gcd, sback, tback};
			return hf;
		} else {
			HeftyInteger[] hf = {gcd, tback, sback};
			return hf;
		}
	}

	private boolean isZero() {
		// All bytes zero
		for (int i = 0; i < this.length(); i++) {
			if (this.getVal()[i] != 0) return false;
		}
		return true;
	}

	public HeftyInteger divide(HeftyInteger other) {

		byte[] thisBytes = this.getVal();
		byte[] newBytes = new byte[this.length()];
		byte[] temp = {0};
		HeftyInteger tempDividend = new HeftyInteger(temp);
		HeftyInteger one = new HeftyInteger(ONE);

		// Count from most significant bit of dividend
		for (int nB = 0; nB < this.length(); nB++) {
			for (int nb = 7; nb >= 0; nb--) {

				int bitLoc = ((this.length() - nB - 1) * 8) + nb;
				int invBitLoc = (8 * this.length()) - bitLoc - 1;

				// Shift and add
				tempDividend = tempDividend.leftShift(1);
				if (getBit(thisBytes, nB, nb) == 1) {
					tempDividend = tempDividend.add(one);
				}

				// If tempDividend big enough, divide
				if (tempDividend.compareTo(other) >= 0) {
					setBit(newBytes, nB, nb, 1);
					tempDividend = tempDividend.subtract(other);
				}
			}
		}

		HeftyInteger quotient = new HeftyInteger(newBytes);
		return quotient.trim();
	}

	public int compareTo(HeftyInteger other) {
		HeftyInteger hf = this.subtract(other);
		if (hf.isZero()) return 0;
		if (hf.isNegative()) return -1;
		return 1;
	}
}
