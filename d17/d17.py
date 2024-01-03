import sys
import re
from collections import defaultdict
   
sys.setrecursionlimit(15000)
 
L = open(sys.argv[1], "r").read().split("\n")

H = []
for l in L:
    H.append([int(x) for x in l])


for l in H:
    print(l)

maxx = len(H[0])-1
maxy = len(H)-1

start = (0,0)
end = (maxx, maxy)
d = (1,0)


sub = ['*', '.']
for l in H:
    v = [sub[x> 0] for x in l]
    print(v)



# Needs A* of some kind