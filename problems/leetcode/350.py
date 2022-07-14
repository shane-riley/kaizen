# Intersection of Two Arrays II
from typing import List
class Solution:
    def intersect(self, nums1: List[int], nums2: List[int]) -> List[int]:
        
        # Get long and short
        long, short = (nums2, nums1) if len(nums2) >= len(nums1) else (nums1, nums2)

        # Map counts
        counts = {}
        for l_val in long:
            if l_val not in counts:
                counts[l_val] = 1
            else:
                counts[l_val] += 1
        
        # Populate array for duplicates
        duplicates = []
        for s_val in short:
            dupe = counts.get(s_val)
            # Skip if not duped
            if dupe is None or dupe == 0:
                continue

            # Add dupe
            duplicates.append(s_val)
            counts[s_val] -= 1

        return duplicates
