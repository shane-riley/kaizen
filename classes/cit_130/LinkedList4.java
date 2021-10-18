import java.util.NoSuchElementException;

/**
 * A Generic, Doubly-Linked List Implementation
 * Class: CIT 130
 * Date: 07/01/2020
 * @author Shane Riley
 * @version 1.0
 */

public class LinkedList4<T extends PubliclyCloneable> implements PubliclyCloneable
{
    //    Node helper class
    private class Node<T extends PubliclyCloneable>
    {
        private T data;
        private Node<T> previous;
        private Node<T> next;

        public Node(T clone, Object o)
        {
            data = null;
            previous = null;
            next = null;
        }

        public Node(T newData, Node<T> newPrevious, Node<T> newNext)
        {
            data = newData;
            previous = newPrevious;
            next = newNext;
        }

        public String toString()
        {
            return data.toString();
        }
    } // end of class

//    Iterator helper class
    public class Iterator<T extends PubliclyCloneable>
    {
        private Node position;

        /**
         * Create iterator at head
         */
        public Iterator()
        {
            position = head;
        }

        /**
         * Restart iterator
         */
        public void restart()
        {
            position = head;
        }

        /**
         * Move to next element in list
         * @return data string stored in current element
         */
        public String next()
        {
            if (!hasNext())
                throw new NoSuchElementException();

            String toReturn = position.data.toString();
            position = position.next;
            return toReturn;
        }

        /**
         * Do not move to next element
         * @return data string stored in current element
         */
        public String peek()
        {
            if (!hasNext())
                throw new NoSuchElementException();

            return position.data.toString();
        }

        public boolean hasNext()
        {
            return (position != null);
        }


    } // end of class

    private Node<T> head;
    private Node<T> tail;

    /**
     * LinkedList4 no-arg constructor
     */
    public LinkedList4()
    {
        head = null;
        tail = null;
    }

    /**
     * LinkedList4 Copy constructor
     */
    public LinkedList4(LinkedList4<T> templateList)
    {
        if (templateList == null)
        {
            throw new NullPointerException();
        }
        else if (templateList.head == null)
        {
            head = null;
            tail = null;
        }
        else
        {
            Node<T>[] headAndTail;
            headAndTail = copyOf(templateList.head);
            head = headAndTail[0];
            tail = headAndTail[1];
        }
    }

    /**
     * LinkedList4 clone method
     */
    public LinkedList4<T> clone()
    {
        try {
            LinkedList4<T> copy =
                    (LinkedList4<T>)super.clone();
            if (head == null)
            {
                copy.head = null;
                copy.tail = null;
            }
            else
            {
                Node<T>[] headAndTail;
                headAndTail = copyOf(head);
                copy.head = headAndTail[0];
                copy.tail = headAndTail[1];
            }
            return copy;
        }
        catch (CloneNotSupportedException e)
        {
            return null;
        }
    }

    /**
     * LinkedList4 copyOf method
     * @return array of head and tail references
     */
    public Node<T>[] copyOf(Node<T> otherHead)
    {
        Node<T> position = otherHead;
        Node<T> newHead;
        Node<T> newTail;
        Node<T> end = null;

        newHead = new Node<T>((T)(position.data).clone(), null, null);
        end = newHead;

        position = position.next;
        while (position != null)
        {
            end.next =
                    new Node<T>((T)(position.data).clone(), end, null);
            end = end.next;
            position = position.next;
        }
        newTail = end;
        return new Node[]{newHead, newTail};
    }

    /**
     * LinkedList4 Iterator method
     */
    public Iterator iterator()
    {
        return new Iterator<T>();
    }

    /**
     * Adds a node at the start of the list with the specified data.
     * The added node will be the first node in the list.
     */
    public void addToStart(T itemData)
    {
        Node<T> oldHead = head;
        if (oldHead == null)
        {
//            If list starts empty, must assign head and tail
            head = new Node<T>(itemData, null, null);
            tail = head;
        }
        else
        {
//            List is not empty. Must set previous for old node
            head = new Node<T>(itemData, null, oldHead);
            oldHead.previous = head;
        }
        //
    }

    /**
     * Removes the head node and returns true if the list contains at least
     * one node. Returns false if the list is empty.
     */
    public boolean deleteHeadNode()
    {
        if (head != null)
        {
            head = head.next; // Move head down a link

//            If list now empty, must clear the tail
            if (head == null)
                tail = null;
//            If not empty must reassign previous
            else
                head.previous = null;

            return true;
        }
        else
            return false;
    }

    /**
     * Returns the number of nodes in the list.
     */
    public int size()
    {
        int count = 0;
        Node<T> position = head;

        while (position != null)
        {
            count++;
            position = position.next;
        }
        return count;
    }

    /**
     * Finds the first node containing the target item, and returns a
     * reference to that node. If the target is not in the list, null is returned.
     */
    private Node<T> find(T target)
    {
        Node<T> position = head;
        T itemAtPosition;
        while (position != null)
        {
            itemAtPosition = position.data;
            if (itemAtPosition.equals(target))
                return position; // found at position
            position = position.next;
        }
        return null; // not found
    }

    /**
     * Finds the first node containing the target and returns a reference
     * to the data in that node. If target is not in the list, null is returned.
     */

    public T findData(T target)
    {
        Node<T> result = find(target);
        if (result == null)
            return null;
        else
            return result.data;
    }

    /**
     * toString method
     * @return A string representing the linked list, returns empty string is list empty
     */
    public String toString()
    {
        Node<T> position = head;
        String outputString = "";

        while(position != null)
        {
            outputString = outputString + position.data.toString() + " ";
            position = position.next;
        }
        return outputString;
    }

    /**
     * Display backwards method
     */
    public void outputBackwards()
    {
        Node<T> position = tail;
        while (position != null)
        {
            System.out.print(position.toString() + " ");
            position = position.previous;
        }
        System.out.println();
    }

    /**
     * For two lists to be equal they must contain the same data items in
     * the same order. The equals method of T is used to compare data items.
     */
    public boolean equals(Object otherObject)
    {
        if (otherObject == null)
            return false;
        else if (getClass() != otherObject.getClass())
            return false;
        else
        {
            LinkedList4<T> otherList = (LinkedList4<T>)otherObject;
            if (size() != otherList.size())
                return false;
            Node<T> position = head;
            Node<T> otherPosition = otherList.head;

            while(position != null)
            {
                if (!(position.data.equals(otherPosition.data)))
                    return false;
                position = position.next;
                otherPosition = otherPosition.next;
            }
            return true;
        }
    }
}
