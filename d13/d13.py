import sys
import re
import numpy as np
from collections import deque

items = open(sys.argv[1], "r").read().split("\n\n")

K = []
for i in items:
    #remove stupid empty strings
    m = filter(None, i.split('\n'))
    K.append(m)
    
sum = 0  
for n in K:

    N = []
    for k in n:
        N.append(list(k))

    NT = []
    for n in np.transpose(N):
        NT.append(list(n))
 
    for i in range(len(N)-1):
        rows = []
        perf = True
        if N[i] == N[i+1]:
            rows.append((i+1, i+2))
            n = 1
            while i-n >= 0 and i+1+n < len(N):
                if N[i-n] == N[i+1+n]:
                    rows.append((1+i-n, 2+i+n))
                else:
                    perf = False
                    break
                n += 1
            if perf:
                sum += 100*rows[0][0]
                break

    for i in range(len(NT)-1):
        cols = []
        perf = True
        if NT[i] == NT[i+1]:
            cols.append((i+1, i+2))
            n = 1
            while i-n >= 0 and i+1+n < len(NT):
                if NT[i-n] == NT[i+1+n]:
                    cols.append((1+i-n, 2+i+n))
                else:
                    perf = False
                    break
                n += 1
            if perf:
                sum += cols[0][0]
                break


print(sum)
