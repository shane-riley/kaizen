/**
 * Test class for figure and its children
 * Class: CIT 130
 * Date: 06/07/2020
 * @author Shane Riley
 * @version 1.0
 */

public class FigureDemo
{
    public static void main(String[] args)
    {
        System.out.println("Figure Drawing Program (Now with Late Binding!)");
        System.out.println();

        Figure[] myFigures = {new Circle("Alice", 0, 0, 10),
                              new Circle("Bob", 5, -5, 2),
                              new Rectangle("Charlie", 0, 0, 4, 10),
                              new Rectangle("Dave", 100, 100, 1, 1)};

        System.out.println(Figure.getNumberOfShapes() + " figures were instantiated.");

        for (Figure figure : myFigures)
        {
            figure.draw();
            System.out.println();
        }
    }
}
