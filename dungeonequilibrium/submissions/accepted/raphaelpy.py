n = int(input())
occ = [0] * (n + 1)
for x in input().strip().split():
    occ[int(x)] += 1
res = 0
for i, o in enumerate(occ):
    if o > i:
        res += o - i
    if o < i:
        res += o
print(res)        
