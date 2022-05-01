/**
 * Copied from text
 * Class: CIT 130
 * Date: 06/06/2020
 */

public class DiscountSale extends Sale
{
    private double discount;

    public DiscountSale()
    {
        super();
        discount = 0;
    }

    public DiscountSale(String theName,
                        double thePrice,
                        double theDiscount)
    {
        super (theName, thePrice);
        setDiscount(theDiscount);
    }

    public DiscountSale(DiscountSale originalObject)
    {
        super (originalObject);
        discount = originalObject.discount;
    }

    public static void announcement()
    {
        System.out.println("This is the DiscountSale class.");
    }

    public double bill()
    {
        double fraction = discount/100;
        return (1-fraction)*getPrice();
    }

    public double getDiscount()
    {
        return discount;
    }

    public void setDiscount(double newDiscount)
    {
        if (newDiscount >= 0)
            discount = newDiscount;
        else
        {
            System.out.println("Error: Negative Discount");
            System.exit(0);
        }
    }

    public String toString()
    {
        return (getName() + " Price = $" + getPrice()
                + " Discount = " + discount + "%\n"
                + " Total cost = $" + bill());
    }

    public boolean equals(Object otherObject)
    {
        if (otherObject == null)
            return false;
        else if (otherObject.getClass() != this.getClass())
            return false;
        else {
            DiscountSale otherDiscount = (DiscountSale) otherObject;
            return (otherDiscount.getDiscount() == this.getDiscount()
                    && otherDiscount.getPrice() == this.getPrice()
                    && otherDiscount.getName().equals(this.getName()));
        }
    }
}
