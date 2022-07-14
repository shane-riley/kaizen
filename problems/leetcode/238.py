## 238. Product of Array Except Self
from typing import List
class Solution:
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        # Three loops (not nested)
        # 1. Generate prefixes
        # 2. Generate suffixes
        # 3. Generate answers
        # O(n) time, O(n) space
        prefixes = [1]*len(nums)
        suffixes = [1]*len(nums)
        answers = [1]*len(nums)
        
        # Generate prefixes
        prefixes[0] = 1
        for i in range(1, len(nums)):
            prefixes[i] = prefixes[i-1] * nums[i-1]
            
        # Generate suffixes
        suffixes[-1] = 1
        for i in range(len(nums) - 2, -1, -1):
            suffixes[i] = suffixes[i+1] * nums[i+1]
            
        # Generate answers
        for i in range(len(answers)):
            answers[i] = prefixes[i] * suffixes[i]
        return answers
