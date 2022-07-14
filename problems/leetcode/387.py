# First Unique Character in a String
from collections import Counter
class Solution:
    def firstUniqChar(self, s: str) -> int:

        # Use the counter subclass of Python dict
        counter = Counter(s)

        # Find the first character counted once
        for i,c in enumerate(s):
            if counter[c] == 1:
                return i
        
        # None found
        return -1
