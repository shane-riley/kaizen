/**
 * De La Braindais (DLB) implementation of UserHistory for Project 2
 * @author	Shane Riley
 */

package cs1501_p2;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;

public class UserHistory implements Dict {

	// Pair for suggest comparison
	class SuggestPair {

		// Instance variables
		String word;
		int num;

		// No-arg constructor
		public SuggestPair(String w, int n) {
			word = w;
			num = n;
		}
	}

	class SuggestComparator implements Comparator<SuggestPair> {
		
		public int compare(SuggestPair r, SuggestPair l) {
			if (r.num > l.num)
				return -1;
			else if (l.num > r.num)
				return 1;
			else
				return 0;
		}
	}

	// Instance variables
	HashMap<String, Integer> table;
	StringBuilder prefix;

    // Noarg constructor
    public UserHistory() {
        table = new HashMap<String, Integer>();
		prefix = new StringBuilder();
    }

    /**
	 * Add a new word to the dictionary
	 *
	 * @param 	key New word to be added to the dictionary
	 */	
	public void add(String key) {
        int val = table.getOrDefault(key, 0);
        table.put(key, val + 1);
	}

	/**
	 * Check if the dictionary contains a word
	 *
	 * @param	key	Word to search the dictionary for
	 *
	 * @return	true if key is in the dictionary, false otherwise
	 */
	public boolean contains(String key) {
		return table.containsKey(key);
	}

	/**
	 * Check if a String is a valid prefix to a word in the dictionary
	 *
	 * @param	pre	Prefix to search the dictionary for
	 *
	 * @return	true if prefix is valid, false otherwise
	 */
	public boolean containsPrefix(String pre) {
		for (String key : table.keySet()) {
			if (key.startsWith(pre)) return true;
		}
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
		
		// Add char to prefix
		int result;
		prefix.append(next);	
		String preString = prefix.toString();
		boolean prefix_found = false, word_found = false;
		for (String key : table.keySet()) {
			if (key.equals(preString)) word_found = true;
			else if (key.startsWith(preString)) prefix_found = true;
		}

		if (word_found) {
			if (prefix_found) result = 2;
			else result = 1;
		} else if (prefix_found) result = 0;
		else result = -1;

		return result;
		
	}

	/**
	 * Reset the state of the current by-character search
	 */
	public void resetByChar() {
		prefix.setLength(0);
	}

	/**
	 * Suggest up to 5 words from the dictionary based on the current
	 * by-character search
	 * 
	 * @return	ArrayList<String> List of up to 5 words that are prefixed by
	 *			the current by-character search
	 */
	public ArrayList<String> suggest() {
		ArrayList<SuggestPair> pairs = new ArrayList<>();
		SuggestPair pair;
		for (String word : table.keySet()) {
			pair = new SuggestPair(word, table.get(word));
			pairs.add(pair);
		}

		// Sort the pairs
		pairs.sort(new SuggestComparator());

		ArrayList<String> al = new ArrayList<>(5);
		int i;
		for (i = 0; i < Math.min(5, pairs.size()); i++) {
			al.add(pairs.get(i).word);
		}

		return al;
	}

	/**
	 * List all of the words currently stored in the dictionary
	 * @return	ArrayList<String> List of all valid words in the dictionary
	 */
	public ArrayList<String> traverse() {
		ArrayList<String> al = new ArrayList<>();
		for (String word : table.keySet()) {
			al.add(word);
		}
		return al;
	}

	/**
	 * Count the number of words in the dictionary
	 *
	 * @return	int, the number of (distinct) words in the dictionary
	 */
	public int count() {
		return table.size();
    }
	
	/**
	 * Get number of occurances for a word
	 * 
	 * @param	word, the word to search
	 * 
	 * @return	int, the number of occurances of the word
	 */
	public int numOccurances(String word) {
		return table.getOrDefault(word, 0);
	}
}
