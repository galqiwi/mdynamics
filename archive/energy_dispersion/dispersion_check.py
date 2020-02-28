import os

UPFS = [2, 3, 4, 5, 8, 11, 16, 22, 32, 45, 64, 90, 128]
NCHECKS = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1 , 1, 1, 1]
NCHECKS = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10000000]
NCHECKS = [256 // x for x in UPFS]
NCHECKS = [1000000 for x in UPFS]

flag = True
while flag:
	flag = False
	for i in range(0, len(UPFS)):
		if NCHECKS[i] == 0:
			continue
		else:
			flag = True
			NCHECKS[i] -= 1
		
		upf = UPFS[i]
		print(upf, NCHECKS, sep='\t')
		os.system('echo {0} | ./bin/main > /dev/null 2>> energy_dispersion'.format(upf))