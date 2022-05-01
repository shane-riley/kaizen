## 2. Add Two Numbers
from typing import Optional
# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        
        carry = False
        
        # Add first num
        l3 = ListNode()
        new_val = l1.val + l2.val
        
        if new_val > 9:
            new_val = new_val - 10
            carry = True
            
        l3.val = new_val
        
        # Copy head
        l3head = l3
        
        # Iterate
        l1 = l1.next
        l2 = l2.next
        
        while l1 and l2:
            
            l3.next = ListNode()
            l3 = l3.next
            
            new_val = l1.val + l2.val + (1 if carry else 0)
            if new_val > 9:
                new_val = new_val - 10
                carry = True
            else:
                carry = False
            l3.val = new_val
            
            l1 = l1.next
            l2 = l2.next
        
        while l1:
            
            l3.next = ListNode()
            l3 = l3.next
            
            new_val = l1.val + (1 if carry else 0)
            if new_val > 9:
                new_val = new_val - 10
                carry = True
            else:
                carry = False
            l3.val = new_val
            
            l1 = l1.next
            
        while l2:
            
            l3.next = ListNode()
            l3 = l3.next
            
            new_val = l2.val + (1 if carry else 0)
            if new_val > 9:
                new_val = new_val - 10
                carry = True
            else:
                carry = False
            l3.val = new_val
            
            l2 = l2.next
        
        if carry:
            l3.next = ListNode(val=1)
        
        return l3head                