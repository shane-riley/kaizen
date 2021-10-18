import javax.swing.JFrame;
import javax.swing.JLabel;
import java.awt.GridLayout;

public class GridLayoutJFrame extends JFrame
{
    public static final int WIDTH = 500;
    public static final int HEIGHT = 400;

    public static void main(String[] args)
    {
        GridLayoutJFrame gui = new GridLayoutJFrame(2, 3);
        gui.setVisible(true);
    }

    public GridLayoutJFrame(int rows, int columns)
    {
        super();
        setSize(WIDTH, HEIGHT);
        setTitle("GridLayout Demonstration");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(rows, columns));

        JLabel label1 = new JLabel("First Label");
        JLabel label2 = new JLabel("Second Label");
        JLabel label3 = new JLabel("Third Label");
        JLabel label4 = new JLabel("Fourth Label");
        JLabel label5 = new JLabel("Fifth Label");
        add(label1);
        add(label2);
        add(label3);
        add(label4);
        add(label5);
    }
}
