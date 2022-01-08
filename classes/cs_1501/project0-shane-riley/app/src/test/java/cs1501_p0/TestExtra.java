package cs1501_p0;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.io.*;

public class TestExtra {

	@Test
	public void testExtraMessage() {
		PrintStream originalOut = System.out;
		ByteArrayOutputStream bos = new ByteArrayOutputStream();
		System.setOut(new PrintStream(bos));

		// action
		Extra.main(null);

		// assertion
		String output = bos.toString();
		assertTrue(output.contains("CS1501"), "Output string does not contain CS1501");

		// undo the binding in System
		System.setOut(originalOut);
	}
}
