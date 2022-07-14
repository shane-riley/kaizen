import java.util.StringTokenizer;
/**
 * Copied from text
 * Class: CIT 130
 * Date: 06/06/2020
 */

public class EnhancedStringTokenizer extends StringTokenizer
{
    private String[] a;
    private int count;

    public EnhancedStringTokenizer(String theString) {
        super(theString);
        a = new String[countTokens()];
        count = 0;
    }

    public EnhancedStringTokenizer(String theString, String delimiters) {
        super(theString, delimiters);
        a = new String[countTokens()];
        count = 0;
    }

    /**
     * Returns the same value as the same method in the StringTokenizer class,
     * but it also stores data for the method tokensSoFar to use.
     *
     * @return token
     */
    public String nextToken() {
        String token = super.nextToken();
        a[count] = token;
        count++;
        return token;
    }

    public String nextToken(String delimiters) {
        String token = super.nextToken(delimiters);
        a[count] = token;
        count++;
        return token;
    }

    public String[] tokensSoFar() {
        String[] arrayToReturn = new String[count];
        for (int i = 0; i < count; i++)
            arrayToReturn[i] = a[i];
        return arrayToReturn;
    }
}
