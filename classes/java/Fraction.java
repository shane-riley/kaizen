/**
 * A class for representing rational numbers
 * Class: CIT 130
 * Date: 06/02/2020
 * @author Shane Riley
 * @version 1.0
 */

public class Fraction
{

    private int numerator;
    private int denominator;

//    No argument constructor for Fraction
    public Fraction()
    {
//        Do nothing
    }

//    Two argument constructor for Fraction
    public Fraction(int a, int b)
    {
        setNumerator(a);
        setDenominator(b);
    }

//    Accessor methods
    public int getNumerator() {
        return numerator;
    }

    public int getDenominator() {
        return denominator;
    }

//    Mutator methods
    public void setNumerator(int numerator) {
        this.numerator = numerator;
    }

    public void setDenominator(int denominator) {
        if (denominator == 0) {
            System.out.println("Cannot divide by zero! Setting denominator to 1...");
            this.denominator = 1;
        }
        else
            this.denominator = denominator;
    }

//    equals method
    public boolean equals(Fraction f)
    {
        return (getNumerator() * f.getDenominator() == f.getNumerator() * getDenominator()); // Check using cross multiplication
    }

//    toString method
    public String toString()
    {
        return numerator + "/" + denominator;
    }
//    toFloat method
    public float toFloat()
    {
        return (float) numerator/denominator;
    }
}
