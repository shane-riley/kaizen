package cs1501_p1;

import org.checkerframework.checker.units.qual.min;

public class BST<T extends Comparable<T>> implements BST_Inter<T> {
    
    // Root node
    private BTNode<T> root;

    // Null constructor
    public BST() {
        // Do nothing (root is null)
    }

    // put method
    public void put(T key) {
        // Null check
        if (this.root != null)
            recPut(key, this.root);
        else
            this.root = new BTNode<T>(key);
    }

    // recPut
    private void recPut(T key, BTNode<T> node) {

        // Precondition: node is not null
        
        if (key.compareTo(node.getKey()) > 0) {
            // New key is higher, go right
            if (node.getRight() != null)
                recPut(key, node.getRight());
            else
                node.setRight(new BTNode<T>(key));
        } else {
            // New key is lower, go left
            if (node.getLeft() != null)
                recPut(key, node.getLeft());
            else
                node.setLeft(new BTNode<T>(key));
        }
    }

    // contains method
    public boolean contains(T key) {
        // Null check
        if (this.root != null)
            return recContains(key, this.root);
        else
            return false;
    }

    // recContains
    private boolean recContains(T key, BTNode<T> node) {
        // Precondition: node is not null

        if (key.compareTo(node.getKey()) == 0)
            return true;
        
        if (key.compareTo(node.getKey()) > 0) {
            // New key is higher, go right
            if (node.getRight() != null)
                return recContains(key, node.getRight());
            else
                return false;
        } else {
            // New key is lower, go left
            if (node.getLeft() != null)
                return recContains(key, node.getLeft());
            else
                return false;
        }
    }

    // delete method
    public void delete(T key) {
        this.root = recDelete(key, this.root);
    }

    // recDelete
    // Returns the new reference to the node
    private BTNode<T> recDelete(T key, BTNode<T> node) {
        
        // Null check
        if (node == null) return null;

        if (key.compareTo(node.getKey()) > 0) {
            node.setRight(recDelete(key, node.getRight()));
            return node;
        }
        else if (key.compareTo(node.getKey()) < 0) {
            node.setLeft(recDelete(key, node.getLeft()));
            return node;
        }
        else {
            // At least one side is null
            if (node.getLeft() == null) return node.getRight();
            if (node.getRight() == null) return node.getLeft();

            // Both sides are not null
            T minRight = findMinKey(node.getRight());

            // Delete min value from right side
            node.setRight(recDelete(minRight, node.getRight()));

            // Replace key
            BTNode<T> newNode = new BTNode<>(minRight);
            newNode.setLeft(node.getLeft());
            newNode.setRight(node.getRight());
            return newNode;
        }

    }

    // findMinKey
    private T findMinKey(BTNode<T> node) {
        // Precondition: node is not null
        T min = node.getKey();
        while ((node = node.getLeft()) != null) {
            if (min.compareTo(node.getKey()) > 0)
                min = node.getKey();
        }
        return min;
    }

    // height method
    public int height() {
        if (this.root != null)
            return recHeight(this.root);
        else
            return 0;
    }

    // recHeight
    private int recHeight(BTNode<T> node) {
        // Precondition: node is not null
        int lHeight = (node.getLeft() != null) ? recHeight(node.getLeft()) : 0;
        int rHeight = (node.getRight() != null) ? recHeight(node.getRight()) : 0;
        return (1 + Math.max(lHeight, rHeight));
    }

    // recMinHeight
    private int recMinHeight(BTNode<T> node) {
        // Precondition: node is not null
        int lHeight = (node.getLeft() != null) ? recHeight(node.getLeft()) : 0;
        int rHeight = (node.getRight() != null) ? recHeight(node.getRight()) : 0;
        return (1 + Math.min(lHeight, rHeight));
    }

    // isBalanced method
    public boolean isBalanced() {

        // Check for null root
        if (this.root == null) return true;

        int lMaxHeight = (this.root.getLeft() != null) ? recHeight(this.root.getLeft()) : 0;
        int lMinHeight = (this.root.getLeft() != null) ? recMinHeight(this.root.getLeft()) : 0;
        int rMaxHeight = (this.root.getRight() != null) ? recHeight(this.root.getRight()) : 0;
        int rMinHeight = (this.root.getRight() != null) ? recMinHeight(this.root.getRight()) : 0;
        
        int maxHeight = Math.max(lMaxHeight, rMaxHeight);
        int minHeight = Math.min(lMinHeight, rMinHeight);
        return (Math.abs(maxHeight - minHeight) < 2);
    }

    // inOrderTraversal method
    public String inOrderTraversal() {
        return recTraversal(this.root);
    }

    // recTraversal
    private String recTraversal(BTNode<T> node) {

        if (node == null) return "";
        String l = recTraversal(node.getLeft());
        String r = recTraversal(node.getRight());

        // Add colons
        if (l.length() > 0) l = l + ":";
        if (r.length() > 0) r = ":" + r;

        return (l + node.getKey().toString() + r);
    }

    // serialize method
    public String serialize() {

        if (this.root == null) return "";
        
        // Preorder
        String rootStr = "R(" + this.root.getKey() + ")";
        String l = (this.root.getLeft() != null) ? "," + recSerial(this.root.getLeft()) : "";
        String r = (this.root.getRight() != null) ? "," + recSerial(this.root.getRight()) : "";
        return rootStr + l + r;
    }

    // recSerial method
    private String recSerial(BTNode<T> node) {
        // Precondition: node is not null

        // Check if leaf
        if (node.getLeft() == null && node.getRight() == null) {
            return "L(" + node.getKey().toString() + ")";
        }

        // Is interior node
        String l = (node.getLeft() != null) ? "," + recSerial(node.getLeft()) : ",X(NULL)";
        String r = (node.getRight() != null) ? "," + recSerial(node.getRight()) : ",X(NULL)";
        return "I(" + node.getKey().toString() + ")" + l + r;
        
    }

    // reverse method
    public BST<T> reverse() {
        BST<T> ret = new BST<>();
        ret.root = recReverse(this.root);
        return ret;
    };

    // recReverse
    private BTNode<T> recReverse(BTNode<T> node) {
        if (node == null) return null;
        BTNode<T> newNode = new BTNode<T>(node.getKey());

        if (node.getRight() != null) {
            newNode.setLeft(recReverse(node.getRight()));
        } else {
            newNode.setLeft(null);
        }

        if (node.getLeft() != null) {
            newNode.setRight(recReverse(node.getLeft()));
        } else {
            newNode.setRight(null);
        }
        return newNode;
    }
}
