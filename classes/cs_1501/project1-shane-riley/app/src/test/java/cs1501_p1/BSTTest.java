package cs1501_p1;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.assertEquals;

import java.io.*;

public class BSTTest {

	private BST<Integer> setup_basic() {
		int[] puts = {5, 1, 10};
		BST<Integer> t = new BST<Integer>();

		for (int i: puts) {
			t.put(i);
		}

		for (int i: puts) {
			assertTrue(t.contains(i), "Cannot check, put/contains not working");
		}

		return t;
	}

	private BST<Integer> setup_unbalanced() {
		int[] puts = {5, 1, 10, -1, 11, 15, 20};
		BST<Integer> t = new BST<Integer>();

		for (int i: puts) {
			t.put(i);
		}

		for (int i: puts) {
			assertTrue(t.contains(i), "Cannot check, put/contains not working");
		}

		return t;
	}

	private BST<Integer> setup_stock() {
		int[] puts = {10, 5, 37, 2, 8, 16, 45};
		BST<Integer> t = new BST<Integer>();

		for (int i: puts) {
			t.put(i);
		}

		for (int i: puts) {
			assertTrue(t.contains(i), "Cannot check, put/contains not working");
		}

		return t;
	}

	private BST<Integer> setup_stock_2() {
		int[] puts = {10, 4, 5, 37, 2, 45, 8, 9, 16};
		BST<Integer> t = new BST<Integer>();

		for (int i: puts) {
			t.put(i);
		}

		for (int i: puts) {
			assertTrue(t.contains(i), "Cannot check, put/contains not working");
		}

		return t;
	}

	private BST<Integer> setup_not_h_b() {
		int[] puts = {5, 4, 3, 2, 1, 6, 7, 8, 9};
		BST<Integer> t = new BST<Integer>();

		for (int i: puts) {
			t.put(i);
		}

		for (int i: puts) {
			assertTrue(t.contains(i), "Cannot check, put/contains not working");
		}

		return t;
	}

	@Test
	public void pc() {
		BST<Integer> t = setup_basic();

		assertTrue(t.contains(5), "Could not find 5");
	}

	@Test
	public void del() {
		BST<Integer> t = setup_basic();

		t.delete(1);
		assertTrue(!t.contains(1), "Could not remove 1");
	}

	@Test
	public void height() {
		BST<Integer> t = setup_basic();

		assertEquals(2, t.height(), "Tree with 5, 1, and 10 should be height 2");
	}

	@Test
	public void height_2() {
		BST<Integer> t = setup_unbalanced();

		assertEquals(5, t.height(), "Wrong");
	}

	@Test
	public void bal() {
		BST<Integer> t = setup_basic();

		assertEquals(true, t.isBalanced(), "Tree with 5, 1, then 10 inserted should be balanced");
	}

	@Test
	public void bal_2() {
		BST<Integer> t = setup_unbalanced();

		assertEquals(false, t.isBalanced(), "Should be unbalanced");
	}

	@Test
	public void iot() {
		BST<Integer> t = setup_basic();

		assertEquals("1:5:10", t.inOrderTraversal(), "Should produce \"1:5:10\"");
	}

	@Test
	public void serial() {
		BST<Integer> t = setup_basic();
		
		assertEquals("R(5),L(1),L(10)", t.serialize(), "Should produce \"R(5),L(1),L(10)\"");
	}

	@Test
	public void rev() {
		BST<Integer> t = setup_basic();

		BST<Integer> r = (BST<Integer>) t.reverse();
		assertEquals("R(5),L(10),L(1)", r.serialize(), "Should produce \"R(5),L(10),L(1)\"");
	}

	@Test
	public void submit() {
		assertTrue(true, "Somehow inproper submission flagged through testing?");
	}

	@Test
	public void stock() {
		BST<Integer> t = setup_stock();
		// assertEquals("R(10),I(5),L(2),X(NULL),I(37),X(NULL),L(45)", t.serialize(), "serial");
		assertEquals("2:5:8:10:16:37:45", t.inOrderTraversal(), "inOrder");


	}

	@Test
	public void stock2() {
		BST<Integer> t = setup_stock_2();
		t.delete(8);
		t.delete(9);
		t.delete(16);
		t.delete(4);
		assertEquals("R(10),I(5),L(2),X(NULL),I(37),X(NULL),L(45)", t.serialize(), "serial");
		// assertEquals("2:5:8:10:16:37:45", t.inOrderTraversal(), "inOrder");

	}

	@Test
	public void notHeightBalanced() {
		BST<Integer> t = setup_not_h_b();
		assertTrue(!t.isBalanced(), "Should not be height balanced");
	}
}
