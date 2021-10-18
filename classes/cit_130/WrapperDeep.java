import java.util.Arrays;

/**
 * Wrapper class with deep copy (int[])
 * Class: CIT 130
 * Date: 06/07/2020
 * @author Shane Riley
 * @version 1.0
 */

public class WrapperDeep {

    public int[] a;

    //    No argument constructor
    public WrapperDeep()
    {
        a = null; // Placeholder
    }

    //    int[] constructor
    public WrapperDeep(int[] arg)
    {
        a = new int[arg.length];
        for (int i = 0; i < arg.length; i++)
            a[i] = arg[i];
    }

    //    Better copy constructor
    public WrapperDeep(WrapperDeep ws)
    {
        int [] wsArray = ws.getArray();
        a = new int[wsArray.length];
        for (int i = 0; i < wsArray.length; i++)
            a[i] = wsArray[i];
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

        WrapperDeep otherWrapper = (WrapperDeep)otherObject;

        return (Arrays.equals(this.getArray(), otherWrapper.getArray()));
    }

    //    setArray
    public void setArray(int[] arg)
    {
        a = new int[arg.length];
        for (int i = 0; i < arg.length; i++)
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
