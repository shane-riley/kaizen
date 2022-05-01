/**
 * Copied from text
 * Class: CIT 130
 * Date: 06/29/2020
 */

public class YourCloneableClass implements Cloneable
{
    public Object clone()
    {
        try
        {
            return super.clone();
        }
        catch (CloneNotSupportedException e)
        {
            return null;
        }
    }
}
