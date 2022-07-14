/**
 * A Publicly Cloneable String Entry for LinkedList4
 * A simple string class with a public clone method
 * Class: CIT 130
 * Date: 07/01/2020
 * @author Shane Riley
 * @version 1.0
 */

public class ListEntry implements PubliclyCloneable
{
    private String data;

    public ListEntry()
    {
        data = null;
    }

    public ListEntry(String inputString)
    {
        data = inputString;
    }

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

    public String toString()
    {
        return data; // immutable object so no issues
    }

    public boolean equals(Object otherObject)
    {
        if (otherObject == null)
            return false;
        else if (getClass() != otherObject.getClass())
            return false;
        else
        {
            ListEntry otherList = (ListEntry)otherObject;
            return (data.equals(otherList.data));
        }
    }
}
