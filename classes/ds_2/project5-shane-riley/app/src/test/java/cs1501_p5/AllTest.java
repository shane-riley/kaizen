/**
 * Basic tests for CS1501 Project 5
 * @author	Dr. Farnan
 */
package cs1501_p5;

import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.assertTimeoutPreemptively;
import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

import java.util.HashMap;
import java.math.BigInteger;
import java.util.Random;

import static java.time.Duration.ofSeconds;

class AllTest {
	final int DEFAULT_TIMEOUT = 19000;

	HashMap<String, String[]> mult_cases;
	HashMap<String, String[]> xgcd_cases;

	@BeforeEach
	void setup_cases() {
		mult_cases = new HashMap<String, String[]>();
		mult_cases.put("4digitA", new String[] {"1834", "5849"});
		mult_cases.put("4digitB", new String[] {"8448", "5593"});
		mult_cases.put("4digitC", new String[] {"8448", "-5593"});
		mult_cases.put("4digitD", new String[] {"-16510656546548549844894984098545465451321718979818198749879876504654654897498789786546548549844894984098545465451321718979818198749879876504654654897498789786546548549844894984098545465451321718979818198749879876504654654897498789786546548549844894984098545465451321718979818198749879876504654654897498789786546548549844894984098545465451321718979818198749879876504654654897498789786546548549844894984098545465451321718979818198749879876504654654897498789784654854984489498409854546545132171897981819874987987650465465489749878978", "-1654654854984489498409854546545132171897981819874987987650465465489749878978654654854984489498409854546545132171897981819874987987650465465489749878978654654854984489498409854546545132171897981819874987987650465465489749878978654654854984489498409854546545132171897981819874987987650465465489749878978654654854984489498409854546545132171897981819874987987650465465489749878978654654854984489498409854546545132171897981819874987987650465465489749878978654654854984489498409854546545132171897981819874987987650465465489749878978654654854984489498409854546545132171897981819874987987650465465489749878978654654854984489498409854546545132171897981819874987987650465465489749878978654654854984489498409854546545132171897981819874987987650465465489749878978654654854984489498409854546545132171897981819874987987650465465489749878978654654854984489498409854546545132171897981819874987987650465465489749878978654654854984489498409854546545132171897981819874987987650465465489749878978654654854984489498409854546545132171897981819874987987650465465489749878978654654854984489498409854546545132171897981819874987987650465465489749878978654654854984489498409854546545132171897981819874987987650465465489749878978"});

		xgcd_cases = new HashMap<String, String[]>();
		xgcd_cases.put("4digitA", new String[] {"2274", "7926"});
		xgcd_cases.put("4digitB", new String[] {"5987", "1488"});
		xgcd_cases.put("4digitC", new String[] {"59046589651651651516516515165165106498448949840985454654513217189798181987498798765046879871956416878984985156165165105621561065046840651032106541695187", "1406505606506520230215165188"});
	}

	void check_mult(String a, String b) {
		BigInteger biA = new BigInteger(a);
		BigInteger biB = new BigInteger(b);

		HeftyInteger hiA = new HeftyInteger(biA.toByteArray());
		HeftyInteger hiB = new HeftyInteger(biB.toByteArray());

		BigInteger biRes = biA.multiply(biB);
		HeftyInteger hiRes = hiA.multiply(hiB);

		assertEquals(0, biRes.compareTo(new BigInteger(hiRes.getVal())));
	}

	void check_xgcd(String a, String b) {
		BigInteger biA = new BigInteger(a);
		BigInteger biB = new BigInteger(b);

		HeftyInteger hiA = new HeftyInteger(biA.toByteArray());
		HeftyInteger hiB = new HeftyInteger(biB.toByteArray());

		HeftyInteger[] hiRes = hiA.XGCD(hiB);

		BigInteger biGCD = biA.gcd(biB);
		HeftyInteger hiGCD = hiRes[0];

		BigInteger x = new BigInteger(hiRes[1].getVal());
		BigInteger y = new BigInteger(hiRes[2].getVal());

		assertEquals(0, biGCD.compareTo(new BigInteger(hiGCD.getVal())));

		BigInteger biCheck = biA.multiply(x).add(biB.multiply(y));

		assertEquals(0, biGCD.compareTo(biCheck));
	}

	@ParameterizedTest(name = "Mult test {0}")
	@ValueSource(strings = {"4digitA", "4digitB", "4digitC", "4digitD"})
	void basic_mult(String c) {
		assertTimeoutPreemptively(ofSeconds(DEFAULT_TIMEOUT), () -> {
			String[] cur = mult_cases.get(c);
			check_mult(cur[0], cur[1]);
		});
	}

	@ParameterizedTest(name = "XGCD test {0}")
	@ValueSource(strings = {"4digitA", "4digitB", "4digitC"})
	void basic_xgcd(String c) {
		assertTimeoutPreemptively(ofSeconds(DEFAULT_TIMEOUT), () -> {
			String[] cur = xgcd_cases.get(c);
			check_xgcd(cur[0], cur[1]);
		});
	}
}
