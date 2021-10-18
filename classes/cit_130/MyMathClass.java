import java.util.ArrayList;
/**
 * A Statistics Class for ArrayLists
 * Class: CIT 130
 * Date: 06/30/2020
 * @author Shane Riley
 * @version 1.0
 */


public class MyMathClass<T extends Number>
{
//    Return an average
    public static <T extends Number> double average(ArrayList<T> a)
    {
        double sum = a.get(0).doubleValue();
        int numElements = a.size();
        for (T element : a)
            sum += element.doubleValue();
        return sum / numElements;
    }

//    Return a standard deviation
    public static <T extends Number> double stdev(ArrayList<T> a) {
        double sumDeviations = 0;
        double mean = average(a);
        int numElements = a.size();
        double value;

//        Sum deviations
        for (T element: a)
        {
            value = element.doubleValue();
            sumDeviations += Math.pow((value - mean), 2);
        }

//        Return standard deviation as double
        return Math.sqrt( (1 / (numElements - 1.0)) * sumDeviations );
    }
}
