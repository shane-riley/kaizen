# Binary Tree Postorder Traversal
from typing import Optional, List
# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    
    def _postorder(self, node: Optional[TreeNode], trav_list):
        if node:
            
            # Trav left
            self._postorder(node.left, trav_list)
            
            # Trav right
            self._postorder(node.right, trav_list)
            
            # Grab value
            trav_list.append(node.val)
            
            
    def postorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        trav_list = []
        self._postorder(root, trav_list)
        return trav_list