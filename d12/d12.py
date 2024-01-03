import sys

lines = open(sys.argv[1], "r").read().split("\n")

R = []
for l in lines:
    x = l.split(" ")
    R.append((list(x[0]), [int(k) for k in x[1].split(',')]))

sub = ['#', '.']
acc = 0

for r in R:
    s, xs = r
    qs = len([q for q in s if q == '?'])
    subs = []
    aq = 0
    for i in range(2**qs):
        subs = [sub[(i>>(j))%2] for j in range(qs)]

        sc = list(''.join(s))
        c = 0
        qc = 0
        while c < len(sc):
            if sc[c] == '?':
                sc[c] = subs[qc]
                qc += 1
            c += 1
        sc = ''.join(sc)
        pats = ['#' * c for c in xs]
        vv = True
        for p in pats:
            hh = 0
            while hh < len(sc) and sc[hh] != '#':
                hh += 1
            pp = 0
            if len(p)+hh == len(sc):
                pp = p
            else:
                pp = p+'.'
            if pp in sc[hh:hh+1+len(p)]:
                sc = sc.replace(pp,"",1)
            else:
                vv = False 
                
        if sc.count('#') > 0:
            vv = False
        if vv:
            aq += 1
    acc += aq
        
print(acc)
