import sys

def solve(a, l, r):
    a.sort()
    n = len(a)
    assert n >= 1
    best = 0
    cur = 0
    for i in range(n // 2):
        cur += -a[i] + a[n - 1 - i]
    best = max(best, cur)
    
    cur = 0
    i, j = 0, n - 1
    cur += l - a[i]
    i += 1
    while i < j and a[j] - l >= 0:
        cur += l - a[i]
        cur += a[j] - l
        i += 1
        j -= 1

    while i <= j and l - a[i] >= 0:
        cur += l - a[i]
        i += 1
        
    best = max(best, cur)

    cur = 0
    i, j = 0, n - 1    
    cur += a[j] - r
    j -= 1
    while i < j and r - a[i] >= 0:
        cur += r - a[i]
        cur += a[j] - r
        i += 1
        j -= 1
    while i <= j and a[j] - r >= 0:
        cur += a[j] - r
        j -= 1
        
    best = max(best, cur)
    
    return best


def main():
    t = int(input())
    for _ in range(t):
        n, l, r = map(int, input().split())
        a = list(map(int, input().split()))
        result = solve(a, l, r)
        print(result)


if __name__ == "__main__":
    main()
