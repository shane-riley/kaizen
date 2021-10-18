/**
 * A class for representing rational numbers
 * Class: CIT 130
 * Date: 06/15/2020
 * @author Shane Riley
 * @version 1.0
 */

public class FractionNew
{

    private int numerator;
    private int denominator;

    //    No argument constructor for FractionNew
    public FractionNew()
    {
//        Do nothing
    }

    //    Two argument constructor for FractionNew
    public FractionNew(int a, int b) throws DenominatorIsZeroException
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

    public void setDenominator(int denominator) throws DenominatorIsZeroException
    {
        if(denominator == 0)
        {
            throw new DenominatorIsZeroException("Cannot use 0 as denominator.");
        }
        else
            this.denominator = denominator;
    }

    //    equals method
    public boolean equals(FractionNew f)
    {
        return (getNumerator() * f.getDenominator() == f.getNumerator() * getDenominator()); // Check using cross multiplication
    }

    //    toString method
    public String toString()
    {
        return numerator + "/" + denominator;
    }
}
