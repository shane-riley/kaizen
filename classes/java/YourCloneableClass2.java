import java.util.Date;
/**
 * Copied from text
 * Class: CIT 130
 * Date: 06/29/2020
 */

public class YourCloneableClass2 implements Cloneable
{
    private Date someVariable; // any mutable class

    public Object clone()
    {
        try {
            YourCloneableClass2 copy = (YourCloneableClass2) super.clone();
            copy.someVariable = (Date) someVariable.clone(); // all mutable instance variables must be dealt with
            return copy;
        } catch (CloneNotSupportedException e) {
            return null;
        }
    }
}
