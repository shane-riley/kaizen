import java.awt.Color;

/**
 * Copied from text
 * Class: CIT 130
 * Date: 07/03/2020
 */

public class ColoredWindowDemo
{
    public static void main(String[] args)
    {
        ColoredWindow w1 = new ColoredWindow();
        w1.setVisible(true);

        ColoredWindow w2 = new ColoredWindow(Color.GRAY);
        w2.setVisible(true);
    }
}
