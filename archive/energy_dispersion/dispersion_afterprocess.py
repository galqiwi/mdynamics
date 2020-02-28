from math import *

with open('energy_dispersion', 'r') as file:
	s = [[float(x) for x in k.split(' ')] for k in file.read().split('\n')[:-1]]


data = {}
for line in s:
	if line[0] in data:
		data[line[0]].append(line[1])
	else:
		data[line[0]] = [line[1]]

def avg(x):
	out = 0
	square = 0
	for x_ in x:
		out += x_
		square += x_ * x_
	out /= len(x)
	square /= len(x)
	return [out, sqrt((square - out * out) / (len(x)))]

for upf in data.keys():
	dispersion, ddispersion = avg(data[upf])
	print(log(1 / upf) / log(10), log(dispersion) / log(10), ddispersion / dispersion / log(10))