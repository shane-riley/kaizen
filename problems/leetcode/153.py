## 153. Find Minimum in Rotated Sorted Array
from typing import List
class Solution:
    def findMin(self, nums: List[int]) -> int:
        # Find i such that nums[i-1] > nums[i] 
        # Or i = 0 iff nums[0] < nums[-1]

        # Check unrotated or single element case
        if nums[0] <= nums[-1]:
            return 0

        # Binary search
        l = 0
        r = len(nums)
        while (r - l > 1):
            m = (r + l) // 2
