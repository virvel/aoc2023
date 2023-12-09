import sys
import re
import math
from collections import defaultdict

string = open(sys.argv[1], "r").read()
lines = string.split("\n")[:-1]
steps, *other = lines
B = string.split("\n\n")[1:][0]
R =re.findall(r"([A-Z0-9]+) = \(([A-Z0-9]+), ([A-Z0-9]+)\)", B)

D = dict()
for r in R:
    D[r[0]] = (r[1], r[2])

def traverse(steps):

    sum = 0
    x = "AAA"
    while x != "ZZZ":
        for s in steps:
            if s == "L":
                x = D[x][0]
            elif s == "R":
                x = D[x][1]
            sum += 1
            if x == "ZZZ":
                break
    return sum


def traverse3(x,steps):

    sum = 0
    while x[-1] != "Z":
        for s in steps:
            if s == "L":
                x = D[x][0]
            elif s == "R":
                x = D[x][1]
            sum += 1
            if x[-1] == "Z":
                break
    return sum


print("p1: ",traverse(steps))

starts = [d for d in D if d[-1] == "A"]

R = []
for s in starts:
    R.append(traverse3(s,steps))


# Part 2 comment
# Every starting value finishes at a certain step N.
# So the product of N_i for 1 < i < number_of_valid_starts
# is a solution to the problem, but not the first/smallest solution.
# In order to find the smallest we need to make sure the 
# multiplicity of each prime factor is minimized.
# The lowest common multiple is exactly that.

print("p2:", math.lcm(*R))
 
