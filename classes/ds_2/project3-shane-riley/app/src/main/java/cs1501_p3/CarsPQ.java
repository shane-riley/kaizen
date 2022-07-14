package cs1501_p3;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.lang.reflect.Array;
import java.util.NoSuchElementException;

public class CarsPQ implements CarsPQ_Inter {

    // PQ Arraylist helper
    public class PQList {

        int n;

        Object[] mileage;
        Object[] price;

        int size() {
            return n;
        }

        IndexMinPQ<PriceCar> getPricePQ(int i) {
            if (i < n + 1) {
                return (IndexMinPQ<PriceCar>) price[i - 1];
            } else {
                return null;
            }
        }

        IndexMinPQ<MileageCar> getMileagePQ(int i) {
            if (i < n + 1) {
                return (IndexMinPQ<MileageCar>) mileage[i - 1];
            } else {
                return null;
            }
        }

        PQList() {
            n = 1;
            // Class<IndexMinPQ<MileageCar>> class1 = new Class;
            // Class<IndexMinPQ<PriceCar>> class2;
            mileage = new Object[10];
            price = new Object[10];
        }

        void makeNewPQ(int i) {
            if (n == price.length) {
                resize(2 * price.length);
            }
            price[i - 1] = new IndexMinPQ<PriceCar>(10);
            mileage[i - 1] = new IndexMinPQ<MileageCar>(10);
            n++;
        }

        void resize(int newSize) {
            Object[] newMileage = new Object[newSize];
            Object[] newPrice = new Object[newSize];
            for (int i = 0; i < mileage.length; i++) {
                newMileage[i] = mileage[i];
                newPrice[i] = price[i];
            }
            price = newPrice;
            mileage = newMileage;
        }
    }

    // Instance variables

    PQList mmPQ;

    // DLB for VIN => i
    DLB vinToIndex;

    // DLB for makeModel to specific PQ
    DLB mmToPQ;

    // PQ for mileage
    IndexMinPQ<MileageCar> allMileagePQ;

    // PQ for price
    IndexMinPQ<PriceCar> allPricePQ;

    // File constructor
    public CarsPQ(String filename) {

        vinToIndex = new DLB();
        allMileagePQ = new IndexMinPQ<>(10);
        allPricePQ = new IndexMinPQ<>(10);
        mmToPQ = new DLB();
        mmPQ = new PQList();

        try {
            // Open file
            BufferedReader bf = new BufferedReader(new FileReader(filename));
            String[] values;
            String line;
            Car c;
            line = bf.readLine(); // Skip header

            // Iterate through lines
            while ((line = bf.readLine()) != null) {
                values = line.strip().split(":");
                assert (values.length == 6);
                c = new Car(values[0], values[1], values[2]);
                c.setPrice(Integer.parseInt(values[3]));
                c.setMileage(Integer.parseInt(values[4]));
                c.setColor(values[5]);
                add(c);
            }
            bf.close();

            // Add to pq's
        } catch (IOException e) {
            System.out.println("IO problem");
        }
    }

    // Add
    public void add(Car c) {

        // Check VIN presence
        if (vinToIndex.contains(c.getVIN())) {
            throw new IllegalStateException();
        }

        // Add to PQ's
        PriceCar pc = new PriceCar(c.getVIN(), c.getMake(), c.getModel());
        pc.setColor(c.getColor());
        pc.setPrice(c.getPrice());
        pc.setMileage(c.getMileage());

        MileageCar mc = new MileageCar(c.getVIN(), c.getMake(), c.getModel());
        mc.setColor(c.getColor());
        mc.setPrice(c.getPrice());
        mc.setMileage(c.getMileage());

        int index = allMileagePQ.size() + 1;

        allMileagePQ.insert(index, mc);
        allPricePQ.insert(index, pc);
        vinToIndex.add(c.getVIN(), index);

        // Add
        String key = c.getMake() + c.getModel();
        int pqIndex = mmToPQ.getIndex(key);
        if (pqIndex == -1) {
            pqIndex = mmPQ.size();
            mmPQ.makeNewPQ(pqIndex);
            mmToPQ.add(key, pqIndex);
        }
        IndexMinPQ<MileageCar> mpq = mmPQ.getMileagePQ(pqIndex);
        mpq.insert(index, mc);
        IndexMinPQ<PriceCar> ppq = mmPQ.getPricePQ(pqIndex);
        ppq.insert(index, pc);

    }

    // Get
    public Car get(String vin) {
        int index = vinToIndex.getIndex(vin);
        if (index == -1) {
            throw new NoSuchElementException();
        }
        return (Car) allMileagePQ.keyOf(index);
    }

    // UpdatePrice
    public void updatePrice(String vin, int newPrice) {
        int index = vinToIndex.getIndex(vin);
        if (index == -1) {
            throw new NoSuchElementException();
        }
        allMileagePQ.keyOf(index).setPrice(newPrice);

    }

    // UpdateMileage
    public void updateMileage(String vin, int newMileage) {
        int index = vinToIndex.getIndex(vin);
        if (index == -1) {
            throw new NoSuchElementException();
        }
        allMileagePQ.keyOf(index).setMileage(newMileage);
    }

    // UpdateColor
    public void updateColor(String vin, String newColor) {
        int index = vinToIndex.getIndex(vin);
        if (index == -1) {
            throw new NoSuchElementException();
        }
        allMileagePQ.keyOf(index).setColor(newColor);

    }

    // Remove
    public void remove(String vin) {
        int index = vinToIndex.getIndex(vin);
        if (index == -1) {
            throw new NoSuchElementException();
        }

        allMileagePQ.delete(index);
        allPricePQ.delete(index);
        vinToIndex.remove(vin);
    }

    // GetLowPrice
    public Car getLowPrice() {
        if (allPricePQ.size() > 0)
            return allPricePQ.minKey();
        else
            return null;
    }

    // GetLowPrice make model
    public Car getLowPrice(String make, String model) {
        if (allPricePQ.size() == 0) {
            return null;
        }
        String key = make + model;
        int pqindex = mmToPQ.getIndex(key);
        if (pqindex == -1) {
            return null;
        }
        return (Car) mmPQ.getPricePQ(pqindex).minKey();
    }

    // GetLowMileage
    public Car getLowMileage() {
        if (allMileagePQ.size() > 0)
            return allMileagePQ.minKey();
        else
            return null;
    }

    // GetLowMileage make model
    public Car getLowMileage(String make, String model) {
        if (allMileagePQ.size() == 0) {
            return null;
        }
        String key = make + model;
        int pqindex = mmToPQ.getIndex(key);
        if (pqindex == -1) {
            return null;
        }
        return (Car) mmPQ.getMileagePQ(pqindex).minKey();
    }
}
