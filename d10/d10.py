import sys
import re
from collections import defaultdict

N = open(sys.argv[1], "r").read().split("\n")[:-1]

S = []
for s in N:
    S.append(list(s)) 

def move(c,p, m):
    match m:
        case '|':
            if c[1] == 1 :
                return (p[0], p[1]+1)
            elif c[1] == -1:
                return (p[0], p[1]-1)
        case '-':
            if c[0] == 1:
                return (p[0]+1, p[1])
            else:
                return (p[0]-1, p[1])
        case 'L':
            if c[0] == -1 :
                return (p[0], p[1]-1)
            elif c[1] == 1:
                return (p[0]+1, p[1])
        case 'J':
            if c[1] == 1:
                return (p[0]-1, p[1])
            elif c[0] == 1:
                return (p[0], p[1]-1)
        case '7':
            if c[0] == 1:
                return (p[0], p[1]+1)
            elif c[1] == -1:
                return (p[0]-1, p[1])
        case 'F':
            if c[0] == -1:
                return (p[0], p[1]+1)
            else:
                return (p[0]+1, p[1])
        case '.':
            return (e, e)
        case 'S':
            return (S, S)
        case _:
            return "?"

p = ()
for i,l in enumerate(N):
    p = (l.find('S'), i)
    if (p[0] >= 0):
        break

c = (0,1)
p = (p[0], p[1]+1)
acc = 1
while p != (S,S): 
    s = S[p[1]][p[0]] 
    m = move(c,p, s)
    if (m == (S,S)):
        break
    c = (m[0] - p[0], m[1] - p[1])
    p = m
    acc += 1

print(acc//2)


