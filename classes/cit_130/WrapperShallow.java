import java.util.Arrays;

/**
 * Wrapper class without deep copy (int[])
 * Class: CIT 130
 * Date: 06/07/2020
 * @author Shane Riley
 * @version 1.0
 */

public class WrapperShallow {

    public int[] a;

//    No argument constructor
    public WrapperShallow()
    {
        a = null; // Placeholder
    }

//    int[] constructor
    public WrapperShallow(int[] arg)
    {
        a = new int[arg.length];
        for (int i = 0; i < arg.length; i++)
            a[i] = arg[i];
    }

//    Badly written copy constructor
    public WrapperShallow(WrapperShallow ws)
    {
        this.a = ws.a; // interesting that IntelliJ does not point out any issues
    }

//    toString method
    public String toString()
    {
//        if a is null, return "(empty)"
        StringBuilder returnString = new StringBuilder();
        if (a == null)
            returnString = new StringBuilder("(empty)");
        else
        {
            for (int value : a)
                returnString.append(value).append(" ");
        }
        return String.valueOf(returnString);
    }

//    equals method
    public boolean equals(Object otherObject)
    {
        if (otherObject == null)
            return false;
        else if (otherObject.getClass() != this.getClass())
            return false;

        WrapperShallow otherWrapper = (WrapperShallow)otherObject;

        return (Arrays.equals(this.a, otherWrapper.a));
    }

//    setArray (assuming arg length == a length
    public void setArray(int[] arg)
    {
        for (int i = 0; i < a.length; i++)
            a[i] = arg[i];
    }

//    getArray
    public int[] getArray()
    {
        int[] b = new int[a.length];
        for (int i = 0; i < a.length; i++)
            b[i] = a[i];
        return b;
    }
}
