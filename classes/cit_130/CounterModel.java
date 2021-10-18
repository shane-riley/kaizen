/**
 * Internal class for Counter
 * Class: CIT 130
 * Date: 06/22/2020
 * @author Shane Riley
 * @version 1.0
 */

public class CounterModel
{
    private int counter;

//    No-arg constructor
    public CounterModel()
    {
        counter = 0;
    }

//    Constructor (no preconditions for counter value)
    public CounterModel(int initialValue)
    {
        counter = initialValue;
    }

//    Increment
    public void Increment() throws InterruptedException
    {
        Thread.sleep(1000);
        counter++;
        CounterView.Display(counter);
    }

//    Accessor method (for use by controller; given package access)
    int getCount()
    {
        return counter;
    }
}
