/**
 * Simple LinkedList implementation for the adjacency lists
 * @author	Shane Riley
 */

package cs1501_p4;

public class myLL {

    private Node root;
    private int size;
    
    // Pseudo-iterator
    private Node point;

    // Constructor
    public myLL() {
        root = null;
        point = null;
        size = 0;
    }

    // Adders
    public void addHead(Link link) {

        // Add at head for speed
        if (size == 0) {
            root = new Node(link);
        } else {
            Node node = root;
            root = new Node(link);
            root.next = node;
        }
        point = root;
        size++;
    }

    public void add(Link link) {

        if (size == 0) {
            root = new Node(link);
        } else {
            Node node = root;
            while (node.hasNext()) { node = node.getNext(); }
            node.next = new Node(link);
        }
        size++;
        point = root;
    }

    // Size
    public int size() {
        return size;
    }

    // Contains
    public boolean contains(int i) {
        if (size == 0) {
            return false;
        } else {
            Node node = root;
            if (node.data.getTo() == i) return true;
            while (node.hasNext()) {
                node = node.getNext();
                if (node.data.getTo() == i) return true;
            }
            return false;
        }
    }

    // Get
    public Link get(int i) {
        if (size == 0) {
            return null;
        } else {
            Node node = root;
            if (node.data.getTo() == i) return node.data;
            while (node.hasNext()) {
                node = node.getNext();
                if (node.data.getTo() == i) return node.data;
            }
            return null;
        }
    }

    // Node helper
    private class Node {

        Link data;
        Node next;

        // Constructor
        private Node(Link data) {
            this.data = data;
        }

        // Getter
        private Link getLink() {
            return data;
        }

        // Setter
        private void setLink(Link link) {
            this.data = link;
        }

        // Has next
        private boolean hasNext() {
            return (next != null);
        }

        // Get next
        private Node getNext() {
            return next;
        }
    }

    // Cannot use the Iterator JCL class, so using our own setup
    public void reset() {
        point = root;
    }

    public boolean hasNext() {
        return (point.next != null);
    }

    public boolean hasThis() {
        return (point != null);
    }

    public Link getNext() {
        point = point.next;
        return (point != null) ? point.data : null;
    }

    public Link getThis() {
        return point.data;
    }

}
