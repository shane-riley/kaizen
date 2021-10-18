import javax.swing.JFrame;
import javax.swing.JButton;

/**
 * Copied from text
 * Class: CIT 130
 * Date: 07/03/2020
 */

public class FirstWindow extends JFrame
{
    public static final int WIDTH = 300;
    public static final int HEIGHT = 200;

    public FirstWindow()
    {
        super();
        setSize(WIDTH, HEIGHT);

        setTitle("First Window Class");
        setDefaultCloseOperation(
                JFrame.DO_NOTHING_ON_CLOSE);

        JButton endButton = new JButton("Click to end program.");
        endButton.addActionListener(new EndingListener());
        add(endButton);
    }
}
