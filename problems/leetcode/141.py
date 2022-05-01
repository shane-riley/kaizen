# Linked List Cycle
from typing import Optional, List
# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None
class Solution:
    
    def _cycle(self, node: Optional[ListNode], nodes: Optional[List[ListNode]]) -> bool:
        if not node: return False
        if node in nodes: return True
        nodes.append(node)
        return self._cycle(node.next, nodes)
        
    
    def hasCycle(self, head: Optional[ListNode]) -> bool:
        nodes = []
        return self._cycle(head, nodes)