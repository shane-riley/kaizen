# Contains Duplicate
from typing import List
class Solution:
    def containsDuplicate(self, nums: List[int]) -> bool:
        # Keep a set of found numbers to easily check for duplication
        # O(n) time, O(n) space
        # A list is a constructor arg for a set in Python
        return (len(nums) > len(set(nums)))