/**
 * De La Braindais (DLB) implementation for Project 2
 * @author	Shane Riley
 */

package cs1501_p2;

import java.util.ArrayList;

public class DLB implements Dict {

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
	 * @param 	key New word to be added to the dictionary
	 */	
	public void add(String key) {

		// Two possible cases
		// 1: key is a prefix for an existing string in the DLB
		// 2: key is not a prefix for an existing string in the DLB

		int i = 0;
		DLBNode newNode;
		

		if (root == null) {
			root = new DLBNode(key.charAt(i));
			searchNode = root;
			i++;
			if (i == key.length()) {
				newNode = new DLBNode(EOS);
				root.setDown(newNode);
				return;
			}
		}

		DLBNode node = root;

		// Start iterating
		while (true) {
			if (node.getLet() == key.charAt(i)) {
				i++;
				if (i == key.length()) {
					// Introduce a new node EOS between node and node and node right
					newNode = new DLBNode(EOS);
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
					newNode = new DLBNode(EOS);
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
	 * @param	key	Word to search the dictionary for
	 *
	 * @return	true if key is in the dictionary, false otherwise
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
						return true;
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

	/**
	 * Check if a String is a valid prefix to a word in the dictionary
	 *
	 * @param	pre	Prefix to search the dictionary for
	 *
	 * @return	true if prefix is valid, false otherwise
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
	 * Search for a word one character at a time
	 *
	 * @param	next Next character to search for
	 *
	 * @return	int value indicating result for current by-character search:
	 *				-1: not a valid word or prefix
	 *				 0: valid prefix, but not a valid word
	 *				 1: valid word, but not a valid prefix to any other words
	 *				 2: both valid word and a valid prefix to other words
	 */
	public int searchByChar(char next) {


		searchPrefix.append(next);

		while (searchNode != null) {
			if (next == searchNode.getLet()) {
				searchNode = searchNode.getDown();
				
				// This node 'should' never be null
				assert (searchNode != null);
				
				if (searchNode.getLet() == EOS) {
					if (searchNode.getRight() != null) {
						return 2;
					} else {
						return 1;
					}
				} else {
					return 0;
				}
			} else {
				searchNode = searchNode.getRight();
			}
		}
		return -1;
	}

	/**
	 * Reset the state of the current by-character search
	 */
	public void resetByChar() {
		searchPrefix.setLength(0);
		searchNode = root;
	}

	/**
	 * Suggest up to 5 words from the dictionary based on the current
	 * by-character search
	 * 
	 * @return	ArrayList<String> List of up to 5 words that are prefixed by
	 *			the current by-character search
	 */
	public ArrayList<String> suggest() {

		ArrayList<String> al = new ArrayList<>(5);
		StringBuilder suggestPrefix = new StringBuilder(searchPrefix);
		// suggestPrefix.setLength(Math.max(suggestPrefix.length() - 1, 0));
		
		// Use recTraverse and then trim
		recTraverse(al, searchNode, suggestPrefix);

		// Trim
		while (5 < al.size()) {
			al.remove(al.size() - 1);
		}
		
		return al;
	}

	/**
	 * List all of the words currently stored in the dictionary
	 * @return	ArrayList<String> List of all valid words in the dictionary
	 */
	public ArrayList<String> traverse() {
		ArrayList<String> al = new ArrayList<>();
		StringBuilder prefix = new StringBuilder();
		recTraverse(al, root, prefix);
		return al;
	}

	private void recTraverse(ArrayList<String> al, DLBNode node, StringBuilder prefix) {
		
		// Assume this node is already added to prefix
		// Null check
		if (node == null) return;

		// If an end of string, append the prefix
		// Else, add to the prefix
		if (node.getLet() == EOS) al.add(prefix.toString());
		else prefix.append(node.getLet());

		// Look down and then look right
		if (node.getDown() != null) {
		
			// Recurse
			recTraverse(al, node.getDown(), prefix);
			
		}
		
		if (node.getRight() != null) {

			// Replace the latest char if not eos
			if (node.getLet() != EOS) prefix.setLength(Math.max(prefix.length() - 1, 0));
	
			// Recurse
			recTraverse(al, node.getRight(), prefix);
	
			// Undo
			if (node.getLet() != EOS) {
			prefix.setLength(Math.max(prefix.length() - 1, 0));
			prefix.append(node.getLet());
			}
		}

		// If not EOS, remove prefix add
		if (node.getLet() != EOS) prefix.setLength(Math.max(prefix.length() - 1, 0));
	}
	
	/**
	 * Count the number of words in the dictionary
	 *
	 * @return	int, the number of (distinct) words in the dictionary
	 */
	public int count() {
		return recCount(root);
	}

	private int recCount(DLBNode node) {
		if (node == null) return 0;

		// Node is not null
		return ((node.getLet() == EOS)?1:0) + recCount(node.getRight()) + recCount(node.getDown());
	}
}
