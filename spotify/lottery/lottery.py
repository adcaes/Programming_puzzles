##============================================================================
## Name        : lottery.py
## Author      : Adria Casas - adria.casas.escoda@gmail.com
## Version     : 1.0
## Description : Solution to Spotify Ticket Lottery puzzle
##============================================================================

import sys
import math 

#Calculates binomial coeficient.
#Returns the number of distinct k-element subsets that can be formed
#from a n-element set.
def binomial(n, k):
    result = 1
    for i in range(1, k+1):
        result = result * (n-k+i)/i
    return result


#m - people in the lottery
#n - num. winners
#t - tickets per winner
#p - people in my group
nums_str = sys.stdin.readline().split()
m, n, t, p = map(int, nums_str)

min_winners = int(math.ceil(float(p)/float(t)))

lose = 0
for win_p in range(0, min_winners):
	lose += binomial(m-p, n-win_p)*binomial(p, win_p)

total = binomial(m, n)

print 1 - (float(lose)/float(total))