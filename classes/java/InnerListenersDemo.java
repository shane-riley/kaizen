import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.GridLayout;
import java.awt.Color;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JMenuBar;

/**
 * Copied from text
 * Class: CIT 130
 * Date: 07/03/2020
 */

public class InnerListenersDemo extends JFrame
{
    public static final int WIDTH = 300;
    public static final int HEIGHT = 200;

    private JPanel bluePanel;
    private JPanel whitePanel;
    private JPanel grayPanel;

    private class BlueListener implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            bluePanel.setBackground(Color.BLUE);
        }
    }
    private class WhiteListener implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            whitePanel.setBackground(Color.WHITE);
        }
    }
    private class GrayListener implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            grayPanel.setBackground(Color.GRAY);
        }
    }

    public static void main(String[] args)
    {
        InnerListenersDemo gui = new InnerListenersDemo();
        gui.setVisible(true);
    }

    public InnerListenersDemo()
    {
        super("Menu Demonstration");
        setSize(WIDTH, HEIGHT);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(1, 3));

        bluePanel = new JPanel();
        bluePanel.setBackground(Color.LIGHT_GRAY);
        add(bluePanel);

        whitePanel = new JPanel();
        whitePanel.setBackground(Color.LIGHT_GRAY);
        add(whitePanel);

        grayPanel = new JPanel();
        grayPanel.setBackground(Color.LIGHT_GRAY);
        add(grayPanel);

        JMenu colorMenu = new JMenu("Add Colors");

        JMenuItem blueChoice = new JMenuItem("Blue");
        blueChoice.addActionListener(new BlueListener());
        colorMenu.add(blueChoice);

        JMenuItem whiteChoice = new JMenuItem("White");
        whiteChoice.addActionListener(new WhiteListener());
        colorMenu.add(whiteChoice);

        JMenuItem grayChoice = new JMenuItem("Gray");
        grayChoice.addActionListener(new GrayListener());
        colorMenu.add(grayChoice);

        JMenuBar bar = new JMenuBar();
        bar.add(colorMenu);
        setJMenuBar(bar);
    }
}
