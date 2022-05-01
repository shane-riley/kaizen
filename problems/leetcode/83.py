# Remove Duplicates from Sorted List
from typing import Optional
# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
class Solution:
    def deleteDuplicates(self, head: Optional[ListNode]) -> Optional[ListNode]:
    
        # Get from node
        to_node = head
        while to_node:
            from_node = to_node
            while to_node and to_node.val == from_node.val:
                to_node = to_node.next
            from_node.next = to_node
        return head
            