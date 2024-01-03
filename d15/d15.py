import sys
import re
import numpy as np
from collections import defaultdict

lines = open(sys.argv[1], "r").read().split("\n")[0].split(',')


def hash(o):
    h = 0
    for c in o:
        h = (h + ord(c))*17%256
    return h

#p1
acc = 0
for l in lines:
    hs = hash(l)
    acc += hs
    
print("part1:", acc)

L = [dict() for x in range(256)]

for l in lines:
    if "=" in l:
        label,f = l.split("=")
        h = hash(label)
        if label not in L[h]:
            L[h][label] = f
        else:
            L[h][label] = f

    elif '-' in l:
        label,f = l.split("-")
        h = hash(label)
        if label in L[h]:
            del L[h][label]

acc = 0
for i,B in enumerate(L):
    for j,b in enumerate(B):
        acc += (i+1)*(j+1)*int(B[b])


print("part2:", acc)
    
