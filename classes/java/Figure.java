/**
 * Parent class for figures
 * Class: CIT 130
 * Date: 06/07/2020
 * @author Shane Riley
 * @version 1.0
 */

public abstract class Figure
{
    private int X, Y; // the center
    private String name;
    private static int numberOfShapes = 0;

    public Figure()
    {
        X = 0;
        Y = 0;
        name = "none";
    }

    public Figure(int a, int b, String n)
    {
        setX(a);
        setY(b);
        setName(n);
        numberOfShapes++;
    }

//    Gets and Sets

    public void setX(int a) {X = a;}
    public void setY(int b) {Y = b;}
    public void setName(String n) {name = n;}
    public int getX() {return X;}
    public int getY() {return Y;}
    public String getName() {return name;}
    public static int getNumberOfShapes() {return numberOfShapes;}

//    Abstract methods (the actions performed will depend on the derived class)

    public abstract void erase();
    public abstract void draw();

//    Center method

    public void center()
    {
        System.out.println("\nIn Figure. Centering at ("+getX()+","+getY()+")");
    }

}
