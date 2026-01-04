missions = []
k = 63
n = k * k * k
size = 1
while size <= 250000:
    for offset in range(k - 1):
        for start in range(n // size - k + 1, -1, -k):
            missions.append((size * (start + offset), size))
    size *= k

print(len(missions))
for m in missions:
    print(m[0], m[1])
