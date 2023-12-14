import sys
import re
import copy
from collections import defaultdict

N = open(sys.argv[1], "r").read().split("\n")[:-1]
sys.setrecursionlimit(1500)

S = []
for s in N:
    S.append(list(s)) 

L = copy.deepcopy(S)


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

T = []
coords = []
c = (0,1)
coords.append((p[0], p[1]))
p = (p[0], p[1]+1)
acc = 1
m = 0
while p != (S,S): 
    s = S[p[1]][p[0]] 
    m = move(c,p, s)
    if (m == (S,S)):
        break
    c = (m[0] - p[0], m[1] - p[1])
    coords.append(p)
    T.append([c,p])
    p = m
    acc += 1

def flood(p, target):
    if (p[0] < 0 or p[1] > len(S)-1 or p[1] < 0 or p[0] > len(S[0])-1):
        return
    if S[p[1]][p[0]] == target or p in coords:
        return
    S[p[1]][p[0]] = target
    flood((p[0], p[1]+1),target)
    flood((p[0], p[1]-1), target)
    flood((p[0]+1, p[1]), target)
    flood((p[0]-1, p[1]), target)

for x in range(len(S[0])):
    for y in range(len(S)):
        if (x == 0 or x == len(S[0])-1) or (y == 0 or y == len(S)-1):
            if (x,y) not in coords:
                flood((x,y), 'O')


for y in range(len(S)):
    for x in range(len(S[0])):

        if S[y][x] not in ['O','I'] and (x,y) not in coords:
            a = 1
            wind = 0
            while x-a >= 0: 
                if S[y][x-a] in ['L', 'J', '|']:
                    wind += 1
                a += 1
            if wind % 2 == 0:
                flood((x,y), 'O')
            else:
                flood((x,y), 'I')

chars = {'F': '┌', '7': '┐', 'L': '└', 'J': '┘', '-': '─', '|': '│', 'S': 'S', '.': ' ', 'O':' ', 'I':' '}
for s in S:
    print(''.join([chars[b] for b in s]))

sum = 0
for s in S:
    sum += s.count('I')

print("part1:",acc//2)
print("part2:",sum)


