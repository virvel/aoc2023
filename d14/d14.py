import sys
import re
import numpy as np
from collections import defaultdict

lines = open(sys.argv[1], "r").read().split("\n")[:-1]

def printm(m, str=""):
    if str:
        print(str)
    for n in m:
        print(''.join(n))

N = []
for l in lines:
    N.append(list(l))


dirs = ['N','W','S','E']
for i in range(20000):
    for d in dirs:
        for y in range(len(N)):
            for x in range(len(N[0])):
                if d == 'N':
                    if N[y][x] == 'O':
                        n = 0
                        while y-n > 0 and N[y-n-1][x] not in ['#', 'O']:
                            n += 1
                        if n > 0:
                            N[y-n][x] = 'O'
                            N[y][x] = '.'

                if d == 'W':
                    if N[y][x] == 'O':
                        n = 0
                        while x-n > 0 and N[y][x-n-1] not in ['#', 'O']:
                            n += 1
                        if n > 0:
                            N[y][x-n] = 'O'
                            N[y][x] = '.'

                if d == 'S':
                    m = len(N)-1
                    if N[m-y][x] == 'O':
                        n = 0
                        while m-y+n < m and N[m-y+n+1][x] not in ['#', 'O']:
                            n += 1
                        if n > 0:
                            N[m-y+n][x] = 'O'
                            N[m-y][x] = '.'

                if d == 'E':
                    m = len(N[0])-1
                    if N[y][m-x] == 'O':
                        n = 0
                        while m-x+n < m and N[y][m-x+n+1] not in ['#', 'O']:
                            n += 1
                        if n > 0:
                            N[y][m-x+n] = 'O'
                            N[y][m-x] = '.'

    M = N.copy()

    acc = 0
    for j,n in enumerate(M):
        acc += sum([x.count('O') for x in n]) * (len(M)-j)
    print("i:",i, "i%28:", i%28, "acc:", acc)

print("\nmod")
printm(N)



# TODO: actually look for the group orbits programmatically
