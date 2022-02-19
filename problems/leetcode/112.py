# Path Sum
from typing import Optional
# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    
    def _pathSum(self, node: Optional[TreeNode], remainingSum: int) -> bool:
        
        # Null check
        if not node: return False
        
        remainingSum -= node.val
        
        if (remainingSum == 0) and not node.left and not node.right:
            return True
        else:
            return self._pathSum(node.left, remainingSum) or self._pathSum(node.right, remainingSum)
    
    def hasPathSum(self, root: Optional[TreeNode], targetSum: int) -> bool:
        return self._pathSum(root, targetSum)
    