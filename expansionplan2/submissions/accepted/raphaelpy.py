import sys

def main():
    _, q = map(int, sys.stdin.readline().strip().split())
    s = sys.stdin.readline().strip()
    v4 = []
    v8 = []
    for c in s:
        v4.append((c == '4') + (v4[-1] if v4 else 0))
        v8.append((c == '8') + (v8[-1] if v8 else 0))

    for _ in range(q):
        l, r, x, y = map(int, sys.stdin.readline().split())
        l -= 1
        r -= 1
        n4 = v4[r] - (v4[l - 1] if l > 0 else 0)
        n8 = v8[r] - (v8[l - 1] if l > 0 else 0)
        x = abs(x)
        y = abs(y)
        n = n4 + n8
        if x <= n and y <= n and x + y <= 2 * n - n4:
            print("YES")
        else:
            print("NO")


if __name__ == "__main__":
    main()
