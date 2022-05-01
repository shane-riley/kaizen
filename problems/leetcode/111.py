# Minimum Depth of Binary Tree
from math import inf
from typing import Optional
# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    
    def _minDepth(self, node: Optional[TreeNode]) -> int:
        
        # Null check (not hit in the case of a leaf)
        if not node: return inf
        
        # Null check right and left
        if not node.right and not node.left: return 1
        
        # Recurse
        return (1 + min(self._minDepth(node.left), self._minDepth(node.right)))
    
    def minDepth(self, root: Optional[TreeNode]) -> int:
        
        if not root: return 0
        return self._minDepth(root)