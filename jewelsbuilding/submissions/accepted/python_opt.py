# better memory
t = int(input())
for _ in range(t):
    n, m = map(int, input().split())
    a = [0] + list(map(int, input().split()))
    b = [0] + list(map(int, input().split()))

    dp0 = [[0 for _ in range(m + 1)] for _ in range(n + 1)]
    dp1 = [[0 for _ in range(m + 1)] for _ in range(n + 1)]
    dp0[0][0] = True

    for i in range(n + 1):
        for j in range(m + 1):
            if i + 1 <= n:
                dp1[i + 1][j] |= dp1[i][j]
            if j + 1 <= m and i + b[j + 1] <= n:
                dp1[i + b[j + 1]][j + 1] |= dp0[i][j]
                dp1[i + b[j + 1]][j + 1] |= dp1[i][j]
            if i + 1 <= n and j + 1 <= m and a[i + 1] == b[j + 1]:
                dp0[i + 1][j + 1] |= dp0[i][j]
                dp0[i + 1][j + 1] |= dp1[i][j]

    if dp0[n][m] or dp1[n][m]:
        print("YES")
    else:
        print("NO")
