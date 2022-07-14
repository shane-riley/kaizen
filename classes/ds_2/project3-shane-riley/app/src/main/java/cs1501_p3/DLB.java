/**
 * De La Braindais (DLB) implementation for Project 2
 * @author	Shane Riley
 */

package cs1501_p3;

public class DLB {

	static final char EOS = '\0';

	// Instance variables
	DLBNode root;
	DLBNode searchNode;
	StringBuilder searchPrefix;

	// No-arg constructor
	public DLB() {
		root = null;
		searchNode = root;
		searchPrefix = new StringBuilder();
	}

	/**
	 * Add a new word to the dictionary
	 *
	 * @param key New word to be added to the dictionary
	 */
	public void add(String key, int index) {

		// Two possible cases
		// 1: key is a prefix for an existing string in the DLB
		// 2: key is not a prefix for an existing string in the DLB

		int i = 0;
		DLBNode newNode;
		DLBNode node;

		if (root == null) {
			root = new DLBNode(key.charAt(i));
			searchNode = root;
			node = root;
			i++;
			// Add down nodes until EOS
			while (i < key.length()) {
				newNode = new DLBNode(key.charAt(i));
				node.setDown(newNode);
				node = node.getDown();
				i++;
			}

			// Add EOS
			newNode = new DLBNode(EOS, index);
			node.setDown(newNode);
			return;
		}

		node = root;

		// Start iterating
		while (true) {
			if (node.getLet() == key.charAt(i)) {
				i++;
				if (i == key.length()) {
					// Introduce a new node EOS between node and node and node right
					newNode = new DLBNode(EOS, index);
					newNode.setRight(node.getRight());
					node.setRight(newNode);
					return;
				} else {
					node = node.getDown();
					assert (node != null);

				}

			} else {
				if (node.getRight() == null) {

					// Add a right node
					newNode = new DLBNode(key.charAt(i));
					node.setRight(newNode);
					node = node.getRight();
					i++;

					// Add down nodes until EOS
					while (i < key.length()) {
						newNode = new DLBNode(key.charAt(i));
						node.setDown(newNode);
						node = node.getDown();
						i++;
					}

					// Add EOS
					newNode = new DLBNode(EOS, index);
					node.setDown(newNode);
					return;

				} else {
					node = node.getRight();
				}
			}
		}

	}

	/**
	 * Check if the dictionary contains a word
	 *
	 * @param key Word to search the dictionary for
	 *
	 * @return true if key is in the dictionary, false otherwise
	 */
	public boolean contains(String key) {

		int i = 0;
		DLBNode node = root;

		while (node != null) {
			if (node.getLet() == key.charAt(i)) {
				// Found this char, iterate down
				node = node.getDown();
				i++;
				// Check for EOS
				if (i == key.length()) {
					// Check for DLB contains EOS
					if (node.getLet() == EOS) {
						return node.index != -1;
					} else {
						return false;
					}
				}
			} else {

				// Move right
				node = node.getRight();
			}
		}

		// Node is null, failed
		return false;
	}

	public int remove(String key) {

		int i = 0;
		DLBNode node = root;

		while (node != null) {
			if (node.getLet() == key.charAt(i)) {
				// Found this char, iterate down
				node = node.getDown();
				i++;
				// Check for EOS
				if (i == key.length()) {
					// Check for DLB contains EOS
					if (node.getLet() == EOS) {
						int ret = node.index;
						node.index = -1;
						return ret;
					} else {
						return -1;
					}
				}
			} else {

				// Move right
				node = node.getRight();
			}
		}

		// Node is null, failed
		return -1;
	}

	public int getIndex(String key) {

		int i = 0;
		DLBNode node = root;

		while (node != null) {
			if (node.getLet() == key.charAt(i)) {

				// System.out.println(node.getLet());
				// Found this char, iterate down
				node = node.getDown();
				i++;
				// Check for EOS
				if (i == key.length()) {
					// Check for DLB contains EOS
					if (node.getLet() == EOS) {
						return node.index;
					} else {
						return -1;
					}
				}
			} else {

				// Move right
				node = node.getRight();
			}
		}

		// Node is null, failed
		return -1;
	}

	/**
	 * Check if a String is a valid prefix to a word in the dictionary
	 *
	 * @param pre Prefix to search the dictionary for
	 *
	 * @return true if prefix is valid, false otherwise
	 */
	public boolean containsPrefix(String pre) {

		int i = 0;
		DLBNode node = root;

		while (node != null) {
			if (node.getLet() == pre.charAt(i)) {
				// Found this char, iterate down
				node = node.getDown();
				i++;
				// Check for EOS
				if (i == pre.length()) {
					// No EOS check, just prefix
					return true;
				}
			} else {

				// Move right
				node = node.getRight();
			}
		}

		// Node is null, failed
		return false;
	}

	/**
	 * Count the number of words in the dictionary
	 *
	 * @return int, the number of (distinct) words in the dictionary
	 */
	public int count() {
		return recCount(root);
	}

	private int recCount(DLBNode node) {
		if (node == null)
			return 0;

		// Node is not null
		return ((node.getLet() == EOS) ? 1 : 0) + recCount(node.getRight()) + recCount(node.getDown());
	}
}
