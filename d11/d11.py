import sys
import re
import numpy as np
from collections import defaultdict

K = open(sys.argv[1], "r").read().split("\n")[:-1]

N = []
for k in K:
    N.append(list(k))

NT = []
for n in np.transpose(N):
    NT.append(list(n))

S = [ (x,y) for y in range(len(N)) for x in range(len(N[0])) if N[y][x] == '#']


def solve(K, m):
    sum = 0
    m = m-1
    while len(K) > 0:
        s = K.pop()
        for g in S:
            xmin = min(g[0], s[0])
            xmax = max(g[0], s[0])
            cls = len([l for l in NT[xmin : xmax] if all([p == '.' for p in l])])
            ymin = min(g[1], s[1])
            ymax = max(g[1], s[1])
            rs = len([l for l in N[ymin : ymax] if all([p == '.' for p in l])])
            sum += abs(g[0]-s[0]) + abs(g[1]-s[1]) + (cls+rs)*m

    return sum

print("part1:", solve(S,2))
S = [ (x,y) for y in range(len(N)) for x in range(len(N[0])) if N[y][x] == '#']
print("part2:", solve(S,1000000))
