## 21. Merge Two Sorted Lists
from typing import Optional
# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
class Solution:
    def mergeTwoLists(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
        
        # Keep one node pointer for each list
        # Make a new list
        # When a pointer's value is lowest, push the value and iterate
        
        # Start the new list
        if list1 and list2:
            if list1.val > list2.val:
                list3 = ListNode(list2.val)
                list2 = list2.next
            else:
                list3 = ListNode(list1.val)
                list1 = list1.next
        elif list1:
            list3 = ListNode(list1.val)
            list1 = list1.next
        elif list2:
            list3 = ListNode(list2.val)
            list2 = list2.next
        else:
            return None

        list3head = list3

        # While both
        while list1 and list2:
            if list1.val > list2.val:
                list3.next = ListNode(list2.val)
                list3 = list3.next
                list2 = list2.next
            else:
                list3.next = ListNode(list1.val)
                list3 = list3.next
                list1 = list1.next
        
        # list2 exhausted
        while list1:
            list3.next = ListNode(list1.val)
            list3 = list3.next
            list1 = list1.next

        while list2:
            list3.next = ListNode(list2.val)
            list3 = list3.next
            list2 = list2.next

        return list3head
