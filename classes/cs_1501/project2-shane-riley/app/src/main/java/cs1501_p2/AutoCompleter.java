/**
 * AutoCompleter class for Project 2
 * @author	Shane Riley
 */

package cs1501_p2;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.FileNotFoundException;
import java.util.ArrayList;

public class AutoCompleter implements AutoComplete_Inter{


	// Instance variables
	DLB dict;
	UserHistory uh;

    // Constructor
    public AutoCompleter(String dictFile, String uhFile) {
		// Initialize DLB
		dict = new DLB();
		uh = new UserHistory();

		// Read from dict file
		try {
			BufferedReader bf = new BufferedReader(new FileReader(dictFile));
			String line;
			while ((line = bf.readLine()) != null) {
				dict.add(line.strip());
			}
			bf.close();
		} catch (Exception e) {
			System.out.println("FAILED TO LOAD DICTIONARY");
		}

		// Read from uh file
		try {
			BufferedReader bf = new BufferedReader(new FileReader(uhFile));
			String line;
			String word;
			int occ;
			while ((line = bf.readLine()) != null) {
				String[] res = line.split("[,]", 0);
				assert (res.length == 2);
				word = res[0].strip();
				occ = Integer.parseInt(res[1]);
				while (occ > 0) {
					uh.add(word);
					occ--;
				}
			}
			bf.close();
		} catch (Exception e) {
			System.out.println("FAILED TO LOAD DICTIONARY");
		}
	}


	// Dictionary-only constructor
    public AutoCompleter(String dictFile) {

		// Initialize DLB
		dict = new DLB();
		uh = new UserHistory();

		// Read from file
		try {
			BufferedReader bf = new BufferedReader(new FileReader(dictFile));
			String line;
			while ((line = bf.readLine()) != null) {
				dict.add(line.strip());
			}
			bf.close();
		} catch (Exception e) {
			System.out.println("FAILED TO LOAD DICTIONARY");
		}
	}

    /**
	 * Produce up to 5 suggestions based on the current word the user has
	 * entered These suggestions should be pulled first from the user history
	 * dictionary then from the initial dictionary
	 *
	 * @param 	next char the user just entered
	 *
	 * @return	ArrayList<String> List of up to 5 words prefixed by cur
	 */	
	public ArrayList<String> nextChar(char next) {
        
		ArrayList<String> al = new ArrayList<>(), al2;

		// Handle dict
		dict.searchByChar(next);
		uh.searchByChar(next);
		
		al = uh.suggest();
		if (al.size() < 5) {
			al2 = new ArrayList<>();
			al2 = dict.suggest();
			for (int i = 0; (al.size() < 5) && (i < al2.size()); i++) {
				al.add(al2.get(i));
			}			
		}
		return al;
    }

	/**
	 * Process the user having selected the current word
	 *
	 * @param 	cur String representing the text the user has entered so far
	 */
	public void finishWord(String cur) {
		uh.add(cur);
		uh.resetByChar();
		dict.resetByChar();
	}

	/**
	 * Save the state of the user history to a file
	 *
	 * @param	fname String filename to write history state to
	 */
	public void saveUserHistory(String fname) {
		try {
			BufferedWriter bf = new BufferedWriter(new FileWriter(fname));
			ArrayList<String> uhWords = uh.traverse();
			for (String word : uhWords) {
				bf.write(word + "," + uh.numOccurances(word) + "\n");
			}
			bf.close();
		} catch (Exception e) {
			System.out.println("FAILED TO WRITE HISTORY");
		}
	}
    
}
