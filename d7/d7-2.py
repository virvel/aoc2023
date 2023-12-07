import sys
import itertools
import copy
from collections import defaultdict

lines = open(sys.argv[1], "r").read().split("\n")[:-1]
strength = {():1, (2,):2, (2,2):3, (3,):4, (2,3):5, (4,):6, (5,):7} 
lex = list(reversed("AKQT98765432J"))

def getStr( card ):
    return strength[tuple(sorted([card.count(x) for x in set(card) if card.count(x) > 1]))]

C = []

for l in lines:
    [card, bid] = l.split(" ")
    maximum = getStr(card)
    if "J" in card:

        chars = list(set([c for c in card if c != "J"]))
        m = [(card,bid,getStr(card.replace("J", c))) for c in chars] 

        m.append((card,bid, maximum))
        C.append(max(m, key = lambda x: x[2]))
    else:
        C.append((card, bid, maximum))


S = sorted(C, key=lambda x : x[2])

sum = 0
acc = 1
for i in range(1,8):
    R = sorted([c for c in S if c[2] == i], key = lambda c : [lex.index(a) for a in c[0]])
    for r in R:
        sum += int(r[1]) * acc
        acc +=1
        

print(sum)
