/**
 * Copied from text
 * Class: CIT 130
 * Date: 07/01/2020
 */

public class Queue
{
    private class Node
    {
        private String item;
        private Node link;

        public Node()
        {
            item = null;
            link = null;
        }

        public Node(String newItem, Node linkValue)
        {
            item = newItem;
            link = linkValue;
        }
    }

    private Node front;
    private Node back;

    public Queue()
    {
        front = null;
        back = null;
    }

    public void addToBack(String itemName)
    {
        Node backNode = new Node(itemName, null);

        if (back == null && front == null)
        {
            front = backNode;
            back = backNode;
        }
        else
        {
            back.link = backNode;
            back = backNode;
        }

    }

    public boolean isEmpty()
    {
        return (front == null);
    }

    public void clear()
    {
        front = null;
        back = null;
    }

    public String whoIsNext()
    {
        if (front == null)
            return null;
        else
            return front.item;
    }

    public boolean removeFront()
    {
        if (front != null)
        {
            front = front.link;
            return true;
        }
        else
            return false;
    }
}
