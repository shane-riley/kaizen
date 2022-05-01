# Symmetric Tree
from typing import Optional
# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    
    def _equalToMirror(self, lnode: Optional[TreeNode], rnode: Optional[TreeNode]) -> bool:
        
        # Null check
        if not lnode or not rnode:
            return not lnode and not rnode
        
        # Check value
        if lnode.val != rnode.val: return False
        
        # check opposites
        return self._equalToMirror(lnode.right, rnode.left) and self._equalToMirror(rnode.right, lnode.left)
    
    def isSymmetric(self, root: Optional[TreeNode]) -> bool:
        if (root):
            return self._equalToMirror(root.left, root.right)
        else:
            return True