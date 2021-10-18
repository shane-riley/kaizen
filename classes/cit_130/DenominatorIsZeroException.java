/**
 * Divide-by-zero Exception thrown by FractionNew
 * Class: CIT 130
 * Date: 06/15/2020
 * @author Shane Riley
 * @version 1.0
 */

public class DenominatorIsZeroException extends Exception
{

//    No-argument constructor

    public DenominatorIsZeroException()
    {
        super("Cannot divide by zero");
    }

//    String argument constructor

    public DenominatorIsZeroException(String message)
    {
        super(message);
    }
}
