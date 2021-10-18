/**
 * Copied from text
 * Class: CIT 130
 * Date: 06/15/2020
 */

public class DivisionByZeroException extends Exception
{
    public DivisionByZeroException()
    {
        super("Division by Zero!");
    }
    public DivisionByZeroException(String message)
    {
        super(message);
    }
}
