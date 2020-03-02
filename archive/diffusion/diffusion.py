from math import *

for line in open('diffusion.data'):
	a, b, c = [float(x) for x in line.split('\t')]
	if a > 0:
		print((a), (c))