/**
 * Car specification for CS1501 Project 3
 * @author	Shane Riley
 */
package cs1501_p3;

public class Car implements Car_Inter {

    // Instance variables
    private String vin;
    private String make;
    private String model;
    private String color;
    private int price;
    private int mileage;

    // Constructor
    public Car(String newVin, String newMake, String newModel) {
        vin = newVin;
        make = newMake;
        model = newModel;
    }

    public Car(String newVin, String newMake, String newModel, int newPrice, int newMileage, String newColor) {
        vin = newVin;
        make = newMake;
        model = newModel;
        price = newPrice;
        mileage = newMileage;
        color = newColor;
    }

    // Getters
    public String getVIN() {
        return vin;
    }

    public String getModel() {
        return model;
    }

    public String getMake() {
        return make;
    }

    public int getPrice() {
        return price;
    }

    public int getMileage() {
        return mileage;
    }

    public String getColor() {
        return color;
    }

    // Setters
    public void setPrice(int newPrice) {
        price = newPrice;
    }

    public void setMileage(int newMileage) {
        mileage = newMileage;
    }

    public void setColor(String newColor) {
        color = newColor;
    }

}
