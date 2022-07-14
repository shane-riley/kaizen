## 110. Balanced Binary Tree
from typing import Optional
# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    def _recBalanced(self, node: Optional[TreeNode]) -> bool:
        
        # Null check
        if not node: return True
        
        if (abs(self._height(node.left) - self._height(node.right)) <= 1):
            return self._recBalanced(node.left) and self._recBalanced(node.right)
        else:
            return False
    
    def _height(self, node: Optional[TreeNode]) -> int:
        
        # Null check
        if not node: return 0
        
        return 1 + max(self._height(node.left), self._height(node.right))
        
    def isBalanced(self, root: Optional[TreeNode]) -> bool:
        return self._recBalanced(root)