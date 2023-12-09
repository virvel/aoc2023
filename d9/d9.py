import sys
import re
from collections import defaultdict

lines = open(sys.argv[1], "r").read().split("\n")

seqs = []
for line in lines[:-1]:
    seqs.append([int(l) for l in line.split()])

sum = 0
sum2 = 0 
for s in seqs:
    step = 0
    D = []
    D.append(s)
    d = s
    while not [0] * len(d) == d:
        d = [int(d[i+1]) - int(d[i]) for i in range(len(d)-1)]
        step += 1
        D.append(d)

    while step > 0:
        D[step-1].append(int(D[step-1][-1]) + int(D[step][-1]))
        D[step-1].insert(0, int(D[step-1][0]) - int(D[step][0]))
        step -= 1

    sum += D[0][-1]
    sum2 += D[0][0]

print(sum)
print(sum2)
