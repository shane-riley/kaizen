# Longest Substring Without Repeating Characters
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        start_index = 0
        best_length = 0
        chars = {}
        for i,c in enumerate(s):
            if c in chars.keys():
                start_index = max(start_index, chars[c] + 1)
            chars[c] = i
            best_length = max(best_length, i - start_index + 1)
        return best_length