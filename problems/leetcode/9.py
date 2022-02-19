# Palindrome number
from math import floor
class Solution:
    def isPalindrome(self, x: int) -> bool:
        if (x < 0): return False
        
        # Naive list scan
        digits = []
        while (x > 0):
            digit = x % 10
            digits.append(digit)
            x = floor(x / 10)
        
        for i in range(floor(len(digits) / 2)):
            if digits[i-1] != digits[-i]:
                return False

        return True
        