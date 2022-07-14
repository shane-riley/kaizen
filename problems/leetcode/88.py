## 88. Merge Sorted Array
from typing import List
class Solution:
    def merge(self, nums1: List[int], m: int, nums2: List[int], n: int) -> None:
        """
        Do not return anything, modify nums1 in-place instead.
        """
        
        
        # To avoid shifting, we will start with the highest values and work backward
        slot = n + m - 1
        p_1 = m - 1
        p_2 = n - 1
        
        while (max(p_1, p_2) > -1):
            if p_1 > -1 and p_2 > -1:
                if nums1[p_1] > nums2[p_2]:
                    nums1[slot] = nums1[p_1]
                    p_1 -= 1
                else:
                    nums1[slot] = nums2[p_2]
                    p_2 -= 1
            elif p_1 > -1:
                nums1[slot] = nums1[p_1]
                p_1 -= 1
            else:
                nums1[slot] = nums2[p_2]
                p_2 -= 1
            slot -= 1