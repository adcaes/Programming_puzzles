'''
https://oj.leetcode.com/problems/min-stack/

Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.
'''

class MinStack:

    def __init__(self):
        self.s = []
        self.mins = []

    # @param x, an integer
    # @return nothing
    def push(self, x):
        if not self.s or self.getMin() >= x:
            self.mins.append(x)
        self.s.append(x)

    # @return nothing
    def pop(self):
        if self.s:
            if self.top() == self.getMin():
                self.mins.pop()
            self.s.pop()

    # @return an integer
    def top(self):
        return self.s[-1] if self.s else None

    # @return an integer
    def getMin(self):
        return self.mins[-1] if self.s else None
