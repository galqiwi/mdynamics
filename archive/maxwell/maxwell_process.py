import os
from math import log

with open('maxwell.datapoints', 'r') as file:
	s = file.read()

s = [[float(x) for x in k.split(' ')] for k in s.split('\n')[:-1]]

N = 100
dx = 5
out = [0] * (N + 1)

def proc(x):
	x = int(abs(x) // dx)
	if x < 0 or x >= N:
		x = N
	return x

for k in s:
	out[proc(k[0])] += 1
	out[proc(k[1])] += 1
	out[proc(k[2])] += 1
	
for id_, x in enumerate(out):
#	print(id_, x)	
	if x > 0:
		print(id_ ** 2, log(x) / log(10))