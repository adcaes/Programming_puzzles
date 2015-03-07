'''
https://oj.leetcode.com/problems/maximum-product-subarray/

Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.
'''

class Solution:

    def diff_sign(self, a, b):
        return (a > 0 and b < 0) or (a < 0 and b > 0)

    # @param A, a list of integers
    # @return an integer
    def maxProduct(self, A):
        if len(A) == 1:
            return A[0]

        total = 0
        total_inv = 0
        maximum = 0

        for i in A:
            if total == 0:
                total = i
            else:
                total *= i

            if total_inv == 0 and self.diff_sign(total, i):
                total_inv = i
            else:
                total_inv *= i

            maximum = max(maximum, max(total, total_inv))

        return maximum
