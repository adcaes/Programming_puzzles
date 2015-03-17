'''
https://leetcode.com/problems/compare-version-numbers/

Compare two version numbers version1 and version2.
If version1 > version2 return 1, if version1 < version2 return -1, otherwise return 0.

You may assume that the version strings are non-empty and contain only digits and the . character.
The . character does not represent a decimal point and is used to separate number sequences.
For instance, 2.5 is not "two and a half" or "half way to version three", it is the fifth second-level revision of the second first-level revision.

Here is an example of version numbers ordering:
0.1 < 1.1 < 1.2 < 13.37
'''

class Solution:
    # @param version1, a string
    # @param version2, a string
    # @return an integer
    def compareVersion(self, version1, version2):
        convert = lambda v: map(int, v.split('.'))
        v1 = convert(version1)
        v2 = convert(version2)

        l = max(len(v1), len(v2))
        v1 += [0]*(l-len(v1))
        v2 += [0]*(l-len(v2))

        for i, j in zip(v1, v2):
            if i > j:
                return 1
            elif i < j:
                return -1

        return 0
