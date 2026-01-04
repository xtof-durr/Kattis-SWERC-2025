import sys


def solve(v):
    for i in range(1, len(v)):
        if v[i - 1] >= v[i]:
            return v[i - 1] // (v[i] - 1)
    d = v[1] - v[0]
    return max(d, v[-1] // d)


def main():
    t = int(input())
    for _ in range(t):
        n = int(input())
        v = list(map(int, input().split()))
        print(solve(v))


if __name__ == "__main__":
    main()