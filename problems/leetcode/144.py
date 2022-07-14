## 144. Binary Tree Preorder Traversal
from typing import Optional, List
# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    
    def _preorder(self, node: Optional[TreeNode], trav_list):
        if node:
            
            # Grab value
            trav_list.append(node.val)
            
            # Trav left
            self._preorder(node.left, trav_list)
            
            # Trav right
            self._preorder(node.right, trav_list)
        
    def preorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        trav_list = []
        self._preorder(root, trav_list)
        return trav_list