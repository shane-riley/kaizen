/**
 * Rectangle drawing class
 * Class: CIT 130
 * Date: 06/07/2020
 * @author Shane Riley
 * @version 1.0
 */

public class Rectangle extends Figure
{
    private int width, height;

    //    Constructors
    public Rectangle()
    {
        super(0,0,"none");
        setWidth(0);
        setHeight(0);
    }

    public Rectangle(String n, int a, int b, int w, int h)
    {
        super(a, b, n);
        setWidth(w);
        setHeight(h);
    }

    //    toString method
    public String toString()
    {
        return ("In Rectangle Drawing " + getName() + " centered at (" + getX() + "," + getY() + ")"
                + " with size of (" + getWidth() + "," + getHeight() + ")");
    }

    //    erase method
    public void erase() {System.out.println("In Rectangle erasing");}

    //    draw method
    public void draw()
    {
        center();
        erase();
        System.out.println(this.toString());
    }

    //    Gets and Sets
    public void setWidth(int w) {
//        Precondition: Cannot be negative
        if (w < 0)
        {
            System.out.println("Error: Negative Width");
            System.exit(0);
        }
        width = w;}

    public void setHeight(int h) {
//        Precondition: Cannot be negative
        if (h < 0)
        {
            System.out.println("Error: Negative Height");
            System.exit(0);
        }
        height = h;}

    public int getWidth() {return width;}
    public int getHeight() {return height;}
}

