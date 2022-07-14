## 108. Convert Sorted Array to Binary Search Tree
from math import floor
from typing import List, Optional
# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    
    def _subsection(self, nums: List[int], left: int, right: int) -> Optional[TreeNode]:
        
        # Empty check
        if (left == right): return None
    
        # Find the middle (root) of the subtree
        middle = floor((right - left)/2 + left)
        
        # Make node with middle
        subroot = TreeNode(nums[middle],
                          left = self._subsection(nums, left, middle),
                          right = self._subsection(nums, middle+1, right))
        return subroot
    
    def sortedArrayToBST(self, nums: List[int]) -> Optional[TreeNode]:
        return self._subsection(nums, 0, len(nums))