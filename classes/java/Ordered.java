/**
 * Copied from text
 * Class: CIT 130
 * Date: 06/29/2020
 */

public interface Ordered
{
    public boolean precedes(Object other);

    /**
     * For objects of the class o1 and o2,
     * o1.follows(o2) == o2.precedes(o1).
     */
    public boolean follows(Object other);
}
