'''
https://oj.leetcode.com/problems/intersection-of-two-linked-lists/

Write a program to find the node at which the intersection of two singly linked lists begins.

Notes:

If the two linked lists have no intersection at all, return null.
The linked lists must retain their original structure after the function returns.
You may assume there are no cycles anywhere in the entire linked structure.
Your code should preferably run in O(n) time and use only O(1) memory.
'''

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    # @param two ListNodes
    # @return the intersected ListNode
    def list_len(self, l):
        length = 0
        while l:
            length += 1
            l = l.next

        return length

    def getIntersectionNode(self, headA, headB):
        lenA = self.list_len(headA)
        lenB = self.list_len(headB)

        if lenA < lenB:
            short, long = headA, headB
            diff = lenB - lenA
        else:
            long, short  = headA, headB
            diff = lenA - lenB

        while diff > 0:
            long = long.next
            diff -= 1

        while short and long:
            if short.val == long.val:
                return short

            short = short.next
            long = long.next

        return None
