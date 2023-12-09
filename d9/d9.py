import sys
import re
from collections import defaultdict

lines = open(sys.argv[1], "r").read().split("\n")

seqs = [l.split(" ") for l in lines][:-1]

sum = 0
for s in seqs:
    step = 0
    D = dict()
    D[step]=s
    d = s
    while not [0] * len(d) == d:
        d = [int(d[i+1]) - int(d[i]) for i in range(len(d)-1)]
        step += 1
        D[step] =d

    while step > 0:
        # Part 1
        #D[step-1].append(int(D[step-1][-1]) + int(D[step][-1]))
        # Part 2
        D[step-1].insert(0, int(D[step-1][0]) - int(D[step][0]))
        step -= 1

    # Part 1
    #sum += D[0][-1]
    # Part 2
    sum += D[0][0]

print(sum)
