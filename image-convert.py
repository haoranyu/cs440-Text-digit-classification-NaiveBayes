#!/usr/bin/python
import sys


def readdataset():
	infile = open(sys.argv[1], 'r')
	outfile = open(sys.argv[1]+'_toi.txt', 'w')

	data = infile.readlines()
	infile.close()
	count =0
	ALLdata = []
	l = len(data)
	i = 0
	while i < l:
		line = data[i].strip('\n ')
		if line:
			print line, ' on line# ', i 
			sample = []
			for k in range (20):
				
				line = data[i].strip('\n')
				#print 'aha string: ', line, ' lenth: ', len(line)
				for j in range(28):
					if line[j] ==' ':
						sample.append('0')
					else:
						sample.append('1')
				i+=1
			count+=1
			#print 'count: ', count, 'sample size: ', len(sample)
			ALLdata.append(sample)
			#print sample
		i+=1

	for sample in ALLdata:
		for v in sample:
			outfile.write(v +' ')
		outfile.write('\n')

	outfile.close()


if __name__ == "__main__":
    readdataset()


