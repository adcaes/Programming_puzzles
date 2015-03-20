'''
https://leetcode.com/problems/binary-search-tree-iterator/

Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.
Calling next() will return the next smallest number in the BST.

Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.
'''

# Definition for a  binary tree node
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class BSTIterator:
    # @param root, a binary search tree's root node
    def __init__(self, root):
        self.stack = []
        self.cur = root
        self.dig()

    # @return a boolean, whether we have a next smallest number
    def hasNext(self):
        return self.cur is not None

    # @return an integer, the next smallest number
    def next(self):
        if self.cur:
            next = self.cur
            if self.cur.right:
                self.cur = self.cur.right
                self.dig()
            elif self.stack:
                self.cur = self.stack.pop()
            else:
                self.cur = None
            return next.val
        return None

    def dig(self):
        while self.cur:
            self.stack.append(self.cur)
            self.cur = self.cur.left
        if self.stack:
            self.cur = self.stack.pop()


# Your BSTIterator will be called like this:
# i, v = BSTIterator(root), []
# while i.hasNext(): v.append(i.next())
