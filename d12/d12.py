import sys
import re
from collections import deque

lines = open(sys.argv[1], "r").read().split("\n")[:-1]

R = []
for l in lines[-6:]:
    x = l.split(" ")
    R.append((x[0], [int(k) for k in x[1].split(',')]))

def trav(s, xs, c):
    if len(xs) == 0:
        return 1
    if len(s) == 0 or xs[-1] > len(s):
        return 0
    print("s: ",s.rjust(20), "\txs: ", xs, "\tc: ", c)


    if s[0] == '.':
        return trav(s[1:], xs, c) 
    if s[0] == '?':
        c = trav('#' + s[1:], xs, c)
        #print("s: ",s.rjust(20), "\txs: ", xs, "\tc: ", c)
        c += trav('.' + s[1:], xs, c)
        #print("s: ",s.rjust(20), "\txs: ", xs, "\tc: ", c)

    i = 0
    if s[0] == '#':
        while (i < len(s) and s[i] not in ['.']):
            i += 1
        print("i:", i)
        if (i == xs[0]):
                return trav('.'+s[xs[0]+1:], xs[1:], c)
        elif (i > xs[0]):
            n = 0
            while n < i and s[n] in ['#', '?']:
                n += 1
            if n == xs[0]: 
                return trav('.'+s[xs[0]+1:], xs[1:], c)
#            
            if xs[0]+1 < len(s) and s[xs[0]] == '#':
                print("X")
                return 0
            if xs[0]+1 < len(s) and s[xs[0]+1] != '#':   
                print("Y")
                return trav('.'+s[xs[0]+1:], xs[1:], c)
            if xs[0]+1 < len(s) and s[xs[0]+1] != '#':   
                print("Z")
                return trav('.'+s[xs[0]+1:], xs[1:], c)
            if xs[0] < len(s) and s[0] == '#':   
                print("W")
                return trav('.'+s[xs[0]+1:], xs[1:], c)
    
        else:
            return 0
        

    return c

L = []
for r in R:
    #r = R[0]
    s, xs = r
#    for x in xs:
#        s = re.sub(r"([\?.]?" + x * '#'+ "[\?.]?)", "", s))
    print(s)
#for i in range(len(S)):
    L.append(trav(s,xs, 0))
#    print(L[-1])

r = R[2]
print(r)
s, xs = r
print(trav(s,xs,0))

print(r[0])

print(L)
v = [1,4,1,1,4,10]
if (L == v):
    print("success!")
else:
    print(" != ")
    print(v)


print(sum(L))
