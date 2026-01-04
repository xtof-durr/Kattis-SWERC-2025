# Mechanical translation of dario_semireverse.cpp into Python
import sys

def solve():
    n = int(input())
    ans = [[-2] * n for _ in range(n)]
    for j in range(n):
        for i in range(j + 1):
            ans[i][j] = -2
            for k in range(i):
                x = ans[k][i - 1]
                y = ans[k][j]
                if x == -2 or y == -2:
                    continue
                if x != y:
                    ans[i][j] = max(x, y)
                if x == -1 and y == -1:
                    ans[i][j] = -1
            
            if ans[i][j] == -2:
                print(f"? {i + 1} {j + 1}", flush=True)
                ans[i][j] = int(input())

    print("!", flush=True)
    for i in range(n):
        print(*(ans[i][j] for j in range(i, n)))
    sys.stdout.flush()

def main():
    t = int(input())
    for _ in range(t):
        solve()

if __name__ == "__main__":
    main()
