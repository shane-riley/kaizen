# Binary Tree Inorder Traversal
from typing import Optional, List
# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    
    def _inorder(self, node: Optional[TreeNode], trav_list):
        if node:
            # Trav left
            self._inorder(node.left, trav_list)
            
            # Grab value
            trav_list.append(node.val)
            
            # Trav right
            self._inorder(node.right, trav_list)
        
    def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        trav_list = []
        self._inorder(root, trav_list)
        return trav_list