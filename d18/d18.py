import sys
   
L = open(sys.argv[1], "r").read().split("\n")

def solve(tups):
    x0 = 0
    y0 = 0

    sigma = 0
    while len(tups) > 0:
        (xn,yn), d = tups.pop(0)
        xn = x0 + (d)*xn
        yn = y0 + (d)*yn

        sigma += x0*yn-xn*y0 + abs(xn-x0) + abs(yn-y0)

        x0 = xn
        y0 = yn

    print(sigma//2 + 1)

ts = []
dirs = {'R': (1,0), 'D': (0,1), 'L':(-1,0), 'U':(0,-1)}
for l in L:
    t = l.split(" ")
    ts.append((dirs[t[0]], int(t[1])))

print("part1")
solve(ts)

hexs = {0: (1,0), 1: (0,1), 2:(-1,0), 3:(0,-1)}
ts = []
for l in L:
    t = l.split(" ")
    ts.append((hexs[int(t[2][-2:-1])],int(t[2][2:-2], 16)))

print("part2")
solve(ts)
