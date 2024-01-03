import sys
import copy
from collections import defaultdict
    
#sys.setrecursionlimit(1500)
L = open(sys.argv[1], "r").read().split("\n")

S = []
for l in L:
    S.append(list(l))

maxx = len(S[0])-1
maxy = len(S)-1

cs = ['/', '\\', '|', '-']
V = []

def trav(tx, tdx, n=0):
    (x,y) = tx
    (dx,dy) = tdx
    n += 1
    if n > 600:
        return

    if x > maxx or y > maxy or x < 0 or y < 0:
        return 
    V[y][x] = '*'
    
    if S[y][x] in cs:
        match S[y][x]:
           case '/':
                if dx == 0:
                    trav((x-dy,y), (-dy,0), n)
                else:
                    trav((x,y-dx), (0,-dx), n)
           case '\\':
               if dx == 0:
                    trav((x+dy,y), (dy,0), n)
               else:
                    trav((x,y+dx), (0,dx), n)
           case '|':
               if dy == 0:
                   trav((x,y+dx), (0,dx), n)
                   trav((x,y-dx), (0,-dx), n)
               else:
                   trav((x,y+dy), (0,dy), n)
           case '-':
               if dx == 0:
                   trav((x-dy,y), (-dy,0), n)
                   trav((x+dy,y), (dy,0), n)
               else:
                   trav((x+dx,y), (dx,0), n)
    else: 
        trav((x+dx,y+dy), (dx,dy), n)


accmax = 0
for y in range(len(S)):
    for x in range(len(S[0])):
        if x == 0 or x == len(S[0])-1 or y == 0 or y == len(S)-1:
            V = copy.deepcopy(S)
            start = (x,y)
            dir = (0,0)
            if x == 0:
                dir = (1,0)
            elif x == len(S[0])-1:
                dir = (-1,0)
            elif y == 0:
                dir = (0,1)
            elif y == len(S)-1:
                dir = (0,-1)
 
            trav( start, dir)

            acc = 0
            for s in V:
                acc += s.count('*')
        
            accmax = max(acc, accmax)
print(accmax)
