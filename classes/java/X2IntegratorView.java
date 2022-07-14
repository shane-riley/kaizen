import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.text.DecimalFormat;

/**
 * A Numerical/Analytical Integrator for f(x) = x^2 (Viewing Class)
 * Class: CIT 130
 * Date: 07/03/2020
 * @author Shane Riley
 * @version 1.0
 */

public class X2IntegratorView extends JFrame implements ActionListener
{
    public final int WIDTH = 500;
    public final int HEIGHT = 300;
    public final int FIELD_SIZE = 15;

    private JTextField startField;
    private JTextField endField;
    private JLabel integralLabel;
    private JLabel numericLabel;
    private JPanel machinePanel;
    private JLabel epsilonLabel;
    private JLabel deltaLabel;
    private JLabel timeLabel;
    private JLabel errorLabel;
    private JButton integrateButton;

    public X2IntegratorView()
    {
        setTitle("X-Squared Integrator");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(WIDTH, HEIGHT);

        JPanel startPanel = new JPanel();
        startPanel.setLayout(new FlowLayout());
        JLabel startLabel = new JLabel("Starting bound:");
        startField = new JTextField(FIELD_SIZE);
        startPanel.add(startLabel);
        startPanel.add(startField);
        add(startPanel);

        JPanel endPanel = new JPanel();
        endPanel.setLayout(new FlowLayout());
        JLabel endLabel = new JLabel("Ending bound:");
        endField = new JTextField(FIELD_SIZE);
        endPanel.add(endLabel);
        endPanel.add(endField);
        add(endPanel);

        integralLabel = new JLabel("Integral Calculator");
        add(integralLabel);

        numericLabel = new JLabel();
        add(numericLabel);

        machinePanel = new JPanel();
        machinePanel.setLayout(new GridLayout(4,1));
        epsilonLabel = new JLabel();
        machinePanel.add(epsilonLabel);
        deltaLabel = new JLabel();
        machinePanel.add(deltaLabel);
        timeLabel = new JLabel();
        machinePanel.add(timeLabel);
        errorLabel = new JLabel();
        machinePanel.add(errorLabel);
        add(machinePanel);

        integrateButton = new JButton("Integrate");
        integrateButton.addActionListener(this);
        add(integrateButton);

        setLayout(new GridLayout(3, 2));
    }

    public static void main(String[] args)
    {
        X2IntegratorView gui = new X2IntegratorView();
        gui.setVisible(true);
    }

    public void actionPerformed(ActionEvent e)
    {
//        Only one possible action to fire in this gui (integrate)

        double start = 0;
        double end = 0;

        String startString = startField.getText();
        String endString = endField.getText();

        try
        {
            start = X2Integrator.checkInput(startString);
            end = X2Integrator.checkInput(endString);

        }
        catch (NumberFormatException e2)
        {
//            Bad inputs, report in numeric field
            numericLabel.setText("Invalid Input. Try again.");
        }

        runIntegral(start, end);
    }

    public void runIntegral(double start, double end)
    {
//        Inputs are valid, run calculations
        double epsilon = X2Integrator.machineEpsilon();
        double delta = X2Integrator.scaleEpsilon(epsilon);

        double anIntegral = X2Integrator.analyticalIntegral(start, end);

//        Run and time numerical integration
        long startTime = System.currentTimeMillis();
        double numIntegral = X2Integrator.numericalIntegral(start, end, delta);
        long endTime = System.currentTimeMillis();
        double time = (endTime - startTime) / 1000.0;

//        Get error
        double error = X2Integrator.getError(anIntegral, numIntegral);

//        Update screen
        epsilonLabel.setText("Machine epsilon: " + String.valueOf(epsilon));
        deltaLabel.setText("Delta: " + String.valueOf(delta));
        errorLabel.setText("Error: " + String.valueOf(error));
        timeLabel.setText("Time: " + String.valueOf(time) + " seconds");
        numericLabel.setText("Numeric answer: " + String.valueOf(numIntegral));

//        Draw integral
        drawIntegral(start, end, anIntegral);
    }

    public void drawIntegral(double start, double end, double ans)
    {
        DecimalFormat df = new DecimalFormat("0.####");
//        Make string
        String outputString = "\u222B" + " x^2 = (1/3)("
                + df.format(start) + " - " + df.format(end) + ") = "
                + df.format(ans);

//        Add string
        integralLabel.setText(outputString);
    }
}
