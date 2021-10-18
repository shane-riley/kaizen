import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JButton;
import java.awt.BorderLayout;
import java.awt.Graphics;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.FlowLayout;

public class ThreadedFillDemo extends JFrame implements ActionListener
{
    public static final int WIDTH = 300;
    public static final int HEIGHT = 200;
    public static final int FILL_WIDTH = 300;
    public static final int FILL_HEIGHT = 100;
    public static final int CIRCLE_SIZE = 10;
    public static final int PAUSE = 100;

    private JPanel box;

    public static void main(String[] args)
    {
        ThreadedFillDemo gui = new ThreadedFillDemo();
        gui.setVisible(true);
    }

    public ThreadedFillDemo()
    {
        setSize(WIDTH, HEIGHT);
        setTitle("Threaded Fill Demo");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        setLayout(new BorderLayout());

        box = new JPanel();
        add(box, "Center");

        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new FlowLayout());
        JButton startButton = new JButton("Start");
        startButton.addActionListener(this);
        buttonPanel.add(startButton);
        add(buttonPanel, "South");
    }

    public void actionPerformed(ActionEvent e)
    {
        Packer packerThread = new Packer();
        packerThread.start();
    }

    private class Packer extends Thread
    {
        public void run()
        {
            Graphics g = box.getGraphics();
            for (int y = 0; y < FILL_HEIGHT; y += CIRCLE_SIZE)
                for (int x = 0; x < FILL_WIDTH; x = x + CIRCLE_SIZE)
                {
                    g.fillOval(x, y, CIRCLE_SIZE, CIRCLE_SIZE);
                    doNothing(PAUSE);
                }
        }

        public void doNothing(int ms)
        {
            try
            {
                Thread.sleep(ms);
            }
            catch (InterruptedException e)
            {
                System.out.println("Unexpected interrupt");
                System.exit(0);
            }
        }
    }
}
