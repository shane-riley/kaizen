/**
 * A Numerical/Analytical Integrator for f(x) = x^2 (Internal Class)
 * Class: CIT 130
 * Date: 07/03/2020
 * @author Shane Riley
 * @version 1.0
 */

public class X2Integrator
{
    final static double EPSILON_SCALING_FACTOR = Math.pow(10, 8);

//    Machine epsilon generator
    public static double machineEpsilon()
    {
        double prevEPS = 1.0;
        double EPS = 1.0;

        while ((1+EPS) != 1)
        {
//            EPS is not small enough
            prevEPS = EPS;

//            Binary shift
            EPS /= 2;
        }

//        PrevEPS is smallest float that will create a change (epsilon)
        return prevEPS;
    }

//    Analytical integral
    public static double analyticalIntegral(double start, double end)
    {
        return (Math.pow(end, 3) - Math.pow(start, 3))/3;
    }

//    Scale epsilon
    public static double scaleEpsilon(double epsilon)
    {
        return epsilon * EPSILON_SCALING_FACTOR;
    }

//    Numerical integral
    public static double numericalIntegral(double start, double end, double delta)
    {
        double area = 0.0;
        double area_increment;
        double location = start;

        // Trivial case
        if (end == start)
            return 0;
        else if (end > start) {
            while (location < end) {
//                Increment location
                location += delta;

//
                area_increment = delta * Math.pow(location, 2);

//                Accumulate
                area += area_increment;
            }
        }
        else
        {
            while (location > end)
            {
//                Increment location
                location -= delta;

//                Create right riemann sum element (will overestimate x^2)
                area_increment = delta * Math.pow(location, 2);

//                Accumulate
                area -= area_increment;
            }
        }
//        Return area
        return area;
    }

//    Get error
    public static double getError(double num1, double num2)
    {
        return Math.abs(num1 - num2);
    }

//    Check inputs
    public static double checkInput(String str1)
    {
        return Double.parseDouble(str1);
    }

//    Internal testing function (NOT FOR GUI)

    public static void main(String[] args)
    {
        double epsilon = machineEpsilon();
        double delta = scaleEpsilon(epsilon);
        System.out.println(epsilon);
        System.out.println(delta);
        double ans = analyticalIntegral(1, 2);
        System.out.println(ans);
        double ans2 = numericalIntegral(1, 2, delta);
        System.out.println(ans2);
        double err = getError(ans, ans2);
        System.out.println(err);
        System.out.println(numericalIntegral(2,1, delta));
    }

}
