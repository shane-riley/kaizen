/**
 * Copied from text
 * Class: CIT 130
 * Date: 07/01/2020
 */

public class IntTree
{
    private static class IntTreeNode
    {
        private int data;
        private IntTreeNode leftLink;
        private IntTreeNode rightLink;

        public IntTreeNode(int newData, IntTreeNode newLeftLink,
                                        IntTreeNode newRightLink)
        {
            data = newData;
            leftLink = newLeftLink;
            rightLink = newRightLink;
        }
    }

    private IntTreeNode root;

    public IntTree()
    {
        root = null;
    }

    public void add(int item)
    {
        root = insertInSubtree(item, root);
    }

    public boolean contains(int item)
    {
        return isInSubtree(item, root);
    }

    public void showElements()
    {
        showElementsInSubtree(root);
    }

    private static IntTreeNode insertInSubtree(int item, IntTreeNode subTreeRoot)
    {
        if (subTreeRoot == null)
            return new IntTreeNode (item, null, null);
        else if (item < subTreeRoot.data)
        {
            subTreeRoot.leftLink = insertInSubtree(item, subTreeRoot.leftLink);
            return subTreeRoot;
        }
        else
        {
            subTreeRoot.rightLink = insertInSubtree(item, subTreeRoot.rightLink);
            return subTreeRoot;
        }
    }

    private static boolean isInSubtree(int item, IntTreeNode subTreeRoot)
    {
        if (subTreeRoot == null)
            return false;
        else if (subTreeRoot.data == item)
            return true;
        else if (item < subTreeRoot.data)
            return isInSubtree(item, subTreeRoot.leftLink);
        else
            return isInSubtree(item, subTreeRoot.rightLink);
    }

    private static void showElementsInSubtree(IntTreeNode subTreeRoot)
    {
        if (subTreeRoot != null)
        {
            showElementsInSubtree(subTreeRoot.leftLink);
            System.out.print(subTreeRoot.data + " ");
            showElementsInSubtree(subTreeRoot.rightLink);
        }
    }
}
