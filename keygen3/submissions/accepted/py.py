# Mechanical translation of sol.cpp into Python.
import sys

def cyc(p):
    vis = [False] * len(p)
    ans = 0
    for i in range(len(p)):
        if vis[i]:
            continue
        ans += 1
        j = i
        while not vis[j]:
            vis[j] = True
            j = p[j]
    return ans

def print_ans(ans):
    print(len(ans))
    for v in ans:
        print(*(len(v)-u for u in reversed(v)))

def resize_all(ans, length):
    for i in range(len(ans)):
        old_len = len(ans[i])
        ans[i].extend(range(old_len, length))
    return ans

def cut(v, n):
    n = min(n, len(v))
    for i in range(n):
        if v[i] >= n:
            return False
    return True

def filter_perms(n, m, k, length):
    ans = []
    p = [0] * n
    for mk in range(1 << (n - 1)):
        if len(ans) == k:
            break
        
        pos = 0
        for j in range(n - 2, -1, -1):
            if (mk >> j) & 1:
                p[pos] = j + 1
                pos += 1
        p[pos] = 0
        pos += 1
        for j in range(n - 1):
            if not ((mk >> j) & 1):
                p[pos] = j + 1
                pos += 1
        
        if cyc(p) == m and cut(p, length):
            ans.append(list(p))
    return ans

def main():
    n, m = map(int, sys.stdin.readline().split())
    k = 2000

    if n <= 18:
        ans = filter_perms(n, m, k, n)
        print_ans(ans)
        return

    if n - m >= 10:
        start_n = 19
        start_m = max(1, start_n - (n - m))
        ans = filter_perms(start_n, start_m, k, n)
        ans = resize_all(ans, n)
        delta = (start_m - start_n) - (m - n)
        for v in ans:
            l, r = v[0] + 1, v[0] + delta
            v[0] = r
            for i in range(1, n):
                if l <= v[i] <= r:
                    v[i] -= 1
        print_ans(ans)
        return

    diff = n - m
    ans = filter_perms(2 * diff + 1, diff + 1, k, n)
    ans = resize_all(ans, n)
    print_ans(ans)

if __name__ == "__main__":
    main()
