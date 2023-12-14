import sys
import re
import numpy as np
from collections import deque

items = open(sys.argv[1], "r").read().split("\n\n")

K = []
for i in items:
    #remove stupid empty strings
    m = list(filter(None, i.split('\n')))
    K.append(m)

    
hamming = lambda s1,s2 : sum(a!=b for (a,b) in zip(s1,s2))

acc = 0  
for z,n in enumerate(K):

    N = []
    for k in n:
        N.append(list(k))

    NT = []
    for n in np.transpose(N):
        NT.append(list(n))
    
    diffs = []
    for i in range(len(N)):
        for j in range(i,len(N)):
            if  1 == hamming(N[i], N[j]):
                diffs.append((i,j))
                diffs.append((j,i))


    diffs = [(1,1)] + diffs
    rres = dict()
    cres = dict()
    for d in diffs:

        tmp = N[d[0]]
        N[d[0]] = N[d[1]]

        for i in range(len(N)-1):
            rows = []
            perf = True
            if N[i] == N[i+1]:
                n = 0
                while i-n >= 0 and i+1+n < len(N):
                    if N[i-n] == N[i+1+n]:
                        rows.append((1+i-n, 2+i+n))
                    else:
                        perf = False
                        break
                    n += 1
                if perf:
                    m = 100 *rows[0][0]
                    if m not in rres.values():
                        rres[d] = m

        N[d[1]] = N[d[0]]
        N[d[0]] = tmp

    #transposed
    diffsT = []
    for i in range(len(NT)):
        for j in range(i,len(NT)):
            if  1 == hamming(NT[i], NT[j]):
                diffsT.append((i,j))
                diffsT.append((j,i))
    diffsT = [(1,1)] + diffsT

    for d in diffsT:
        tmpT = NT[d[0]]
        NT[d[0]] = NT[d[1]]
        for i in range(len(NT)-1):
            cols = []
            perf = True
            if NT[i] == NT[i+1]:
                n = 0
                while i-n >= 0 and i+1+n < len(NT):
                    if NT[i-n] == NT[i+1+n]:
                        cols.append((1+i-n, 2+i+n))
                    else:
                        perf = False
                        break
                    n += 1
                if perf:
                    m = cols[0][0]
                    if m not in cres.values():
                        cres[d] = m  
        NT[d[1]] = NT[d[0]]
        NT[d[0]] = tmpT

    rres.pop((1,1), None)
    cres.pop((1,1), None)

    rvals = list(set(rres.values()))
    cvals = list(set(cres.values()))
    
    for r in rvals:
        acc += r

    for c in cvals:
        acc += c
    
print(acc)
