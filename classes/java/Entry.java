/**
 * Copied from text
 * Class: CIT 130
 * Date: 07/01/2020
 */

public class Entry
{
    private String item;
    private int count;

    public Entry(String itemData, int countData)
    {
        item = itemData;
        count = countData;
    }

    public String toString()
    {
        return (item + " " + count);
    }

    public boolean equals(Object otherObject)
    {
        if (otherObject == null)
            return false;
        else if (getClass() != otherObject.getClass())
            return false;
        else
        {
            Entry otherEntry = (Entry)otherObject;
            return (item.equals(otherEntry.item)
                    && (count == otherEntry.count));
        }
    }
}
