## 1. Two Sum
from typing import List
class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:    
        seen_nums = {}
        for i,v in enumerate(nums):
            needed_val = target - v
            if needed_val in seen_nums.keys():
                return [i, seen_nums[needed_val]]
            else:
                seen_nums[v] = i
                