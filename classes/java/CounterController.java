/**
 * Input class for Counter
 * Class: CIT 130
 * Date: 06/22/2020
 * @author Shane Riley
 * @version 1.0
 */

public class CounterController
{
    private int startValue;
    private int endValue;

//    Constructor (one precondition)
    public CounterController(int start, int end)
    {
        if (end <= start)
        {
            System.out.println("end value must be greater than start value.");
            System.exit(0);
        }
        else
        {
            startValue = start;
            endValue = end;
        }
    }

//    Start
    public void Start()
    {
//        Create a CounterModel
        CounterModel count = new CounterModel(startValue);

        try {
            while (count.getCount() < endValue) {
                count.Increment();
            }
        }
        catch (InterruptedException e) {
            System.out.println(e.getMessage());
            System.exit(0);
        }
    }
}
