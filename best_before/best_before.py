##============================================================================
## Name        : best_before.py
## Author      : Adria Casas - adria.casas.escoda@gmail.com
## Version     : 1.0
## Description : Solution to Spotify Best before puzzle
##============================================================================

import sys
import itertools
import datetime

line = sys.stdin.readline().splitlines()[0]
nums_str = line.split("/")

nums = map(int, nums_str)

if len(nums) == 3:
	found = False
	first = datetime.date(2999, 12, 31)
	
	#Generate all the permutations and usign datetime.date find 
	#the earliest valid date between the range 2000 - 2999
	for perm in itertools.permutations(nums):
		year = perm[0]
		if year < 1000:
			year += 2000
		
		if year >= 2000 and year <= 2999:
			try:
				d = datetime.date(year, perm[1], perm[2])
				if d <= first:
					first = d
					found = True
			except ValueError:
				continue
	
	if found:
		print first
	else:
		print line + " is illegal"
else:
	print line + " is illegal"
				
			
	
	
	