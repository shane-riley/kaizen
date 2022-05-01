import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JButton;
import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.Color;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/**
 * Copied from text
 * Class: CIT 130
 * Date: 07/03/2020
 */

// Not currently functional (IntelliJ)

public class IconDemo extends JFrame implements ActionListener
{
    public static final int WIDTH = 500;
    public static final int HEIGHT = 200;
    public static final int TEXT_FIELD_SIZE = 30;

    private JTextField message;

    public static void main(String[] args)
    {
        IconDemo iconGui = new IconDemo();
        iconGui.setVisible(true);
    }

    public IconDemo()
    {
        super("Icon Demonstration");
        setSize(WIDTH, HEIGHT);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        setBackground(Color.WHITE);
        setLayout(new BorderLayout());

        JLabel dukeLabel = new JLabel("Mood check");
        ImageIcon dukeIcon = new ImageIcon("/icons/duke_waving.png");
        dukeLabel.setIcon(dukeIcon);
        add(dukeLabel, BorderLayout.NORTH);

        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new FlowLayout());
        JButton happyButton = new JButton("Happy");
        ImageIcon happyIcon = new ImageIcon("/icons/smile.png");
        happyButton.setIcon(happyIcon);
        happyButton.addActionListener(this);
        buttonPanel.add(happyButton);
        JButton sadButton = new JButton("Sad");
        ImageIcon sadIcon = new ImageIcon("/icons/frown.png");
        sadButton.setIcon(sadIcon);
        sadButton.addActionListener(this);
        buttonPanel.add(sadButton);
        add(buttonPanel, BorderLayout.SOUTH);

        message = new JTextField(TEXT_FIELD_SIZE);
        add(message, BorderLayout.CENTER);
    }

    public void actionPerformed(ActionEvent e)
    {
        String actionCommand = e.getActionCommand();
        if (actionCommand.equals("Happy"))
            message.setText(
                    "Smile and the world smiles with you!");
        else if (actionCommand.equals("Sad"))
            message.setText(
                    "Cheer up. It can't be that bad");
        else
            message.setText("Unexpected Error.");
    }
}
