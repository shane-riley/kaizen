## 53. Maximum Subarray
from typing import List
class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        
        # Grab first number
        maxSub = nums[0]
        
        # Sum
        curSum = 0
        for n in nums :
            
            # If culmulative sum is less than zero, drop those terms
            if curSum <0:
                curSum = 0 
            
            # Add the number
            curSum += n
            
            # Track max
            maxSub = max(maxSub,curSum) 
        
        return maxSub