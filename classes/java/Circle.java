/**
 * Circle drawing class
 * Class: CIT 130
 * Date: 06/07/2020
 * @author Shane Riley
 * @version 1.0
 */

public class Circle extends Figure
{
    private int radius;

//    Constructors
    public Circle()
    {
        super(0,0,"none");
        setRadius(0);
    }

    public Circle(String n, int a, int b, int r)
    {
        super(a, b, n);
        setRadius(r);
    }

//    toString method
    public String toString()
    {
        return ("In Circle Drawing " + getName() + " centered at (" + getX() + "," + getY() + ") with radius " + getRadius());
    }

//    erase method
    public void erase() {System.out.println("In Circle erasing");}

//    draw method
    public void draw()
    {
        center();
        erase();
        System.out.println(this.toString());
    }

//    Gets and Sets
    public void setRadius(int r)
    {
//        Precondition: cannot be negative
        if (r < 0)
        {
            System.out.println("Error: Negative Radius");
            System.exit(0);
        }
        radius = r;
    }
    public int getRadius() {return radius;}
}
