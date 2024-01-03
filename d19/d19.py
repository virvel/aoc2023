import sys
   
L = open(sys.argv[1], "r").read().split("\n\n")

instr = L[0].split("\n")
xmas = L[1].split("\n")

ins = {}
for i in instr:
    a,b = i.split('{')
    ins[a] = b.strip("}").split(",")

y = []
for x in xmas:
    x = x.strip("{}").split(",")
    yy = {}
    for i in x:
        xx = i.split('=')
        yy[xx[0]] = int(xx[1]) 
    y.append(yy)

acc = 0
for x in y:
    i = 'in'
    while i not in ['A', 'R']:
        inn = ins[i]
        for j in inn:
            if len(j.split(':')) == 1:
                i = inn[-1]
                break
            if j[0] in ['x', 'm' , 'a', 's']:
                ret = j.split(':')
                if j[1] == '<' and x[j[0]] < int(ret[0][2:]):
                    i = ret[-1]
                    break
                if j[1] == '>' and x[j[0]] > int(ret[0][2:]):
                    i = ret[-1]
                    break
    if i == 'A':
        for b in x:
            acc += x[b]

def trav(xx, key):
    acc = 0

    if key == 'A':
        sigma = 1
        for x in xx:
            sigma *= xx[x][1]+1 - xx[x][0]
        acc += sigma
        return acc
    if key == 'R':
        return 0

    inn = ins[key]
    xs = xx.copy()
    for j in inn:
        ret = j.split(':')
        if len(ret) == 1:
            acc += trav(xs,ret[0])
            break
        if j[0] in ['x', 'm', 'a', 's']:
            a,b = xs[j[0]]
            c = int(ret[0][2:])
            if j[1] == '<':
                if b < c:
                    acc += trav(xs, ret[0])
                else:
                    if a < c:
                        xs[j[0]] = (a,c-1)
                        acc += trav(xs,ret[-1])
                        xs[j[0]] = (c,b)
                    else:
                        acc += trav(xs,ret[-1])
            if j[1] == '>':
                if a > int(ret[0][2:]):
                    acc += trav(xs, ret[-1])
                else:
                    if b > int(ret[0][2:]):
                        xs[j[0]] = (c+1,b)
                        acc += trav(xs,ret[-1])                            
                        xs[j[0]] = (a,c)
                    else:
                        acc += trav(xs,ret[-1])
 
    return acc



x = {'x':(1,4000), 'm':(1,4000), 'a':(1,4000), 's':(1,4000)}
res = trav(x, 'in')

print(res)
print(acc)

