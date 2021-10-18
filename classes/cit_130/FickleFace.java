import javax.swing.JFrame;
import javax.swing.JButton;
import java.awt.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/**
 * A Basic Graphics Display
 * Class: CIT 130
 * Date: 07/03/2020
 * @author Shane Riley
 * @version 1.0
 */

public class FickleFace extends JFrame
{
    public static final int WINDOW_WIDTH = 400;
    public static final int WINDOW_HEIGHT = 400;
    public static final int FACE_DIAMETER = 200;
    public static final int X_FACE = (WINDOW_WIDTH - FACE_DIAMETER) / 2;
    public static final int Y_FACE = (WINDOW_HEIGHT - FACE_DIAMETER) / 2;

    public static final int EYE_WIDTH = 20;
    public static final int EYE_HEIGHT = 10;
    public static final int EYE_SPACING = 75;
    public static final int Y_EYE = 60;

    public static final int X_EYE = X_FACE + 90;
    public static final int X_RIGHT_EYE = X_EYE - EYE_SPACING/2;
    public static final int X_LEFT_EYE =  X_EYE + EYE_SPACING/2;
    public static final int Y_RIGHT_EYE = Y_FACE + Y_EYE;
    public static final int Y_LEFT_EYE = Y_RIGHT_EYE;

    public static final int MOUTH_WIDTH = 100;
    public static final int MOUTH_HEIGHT = 50;
    public static final int X_MOUTH = X_FACE + 50;
    public static final int Y_MOUTH = Y_FACE + 100;
    public static final int MOUTH_START_ANGLE = 180;
    public static final int MOUTH_ARC_SWEEP = 180;

    private boolean smile;
    private JButton toggleButton;

    private class FaceAction implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            if (smile)
                toggleButton.setText("Smile");
            else
                toggleButton.setText("Frown");

            smile = !smile;
            repaint();
        }
    }

    public static void main(String[] args)
    {
        FickleFace gui = new FickleFace();
        gui.setVisible(true);
    }

    public FickleFace()
    {
        setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setTitle("Fickle Face");
        setLayout(new BorderLayout());
        getContentPane().setBackground(Color.WHITE);

        toggleButton = new JButton("Smile");
        toggleButton.addActionListener(new FaceAction());
        add(toggleButton, BorderLayout.SOUTH);
        smile = false;
    }

    public void paint(Graphics g)
    {
        super.paint(g);
        g.drawOval(X_FACE, Y_FACE, FACE_DIAMETER, FACE_DIAMETER);

//        Eyes
        g.fillOval(X_RIGHT_EYE, Y_RIGHT_EYE, EYE_WIDTH, EYE_HEIGHT);
        g.fillOval(X_LEFT_EYE, Y_LEFT_EYE, EYE_WIDTH, EYE_HEIGHT);

//        Mouth
        if (smile)
            g.drawArc(X_MOUTH, Y_MOUTH, MOUTH_WIDTH, MOUTH_HEIGHT,
                    MOUTH_START_ANGLE, MOUTH_ARC_SWEEP);
        else
            g.drawArc(X_MOUTH, Y_MOUTH, MOUTH_WIDTH, MOUTH_HEIGHT,
                    MOUTH_START_ANGLE, -1 * MOUTH_ARC_SWEEP);
    }
}
