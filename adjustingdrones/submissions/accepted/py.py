# Mechanical translation of sol.cpp.

import sys

def solve():
    n, k = map(int, input().split())
    v = list(map(int, input().split()))

    def check_zero():
        freq = [0] * (2 * n + 1)
        for x in v:
            freq[x] += 1
        for x in freq:
            if x > k:
                return False
        return True

    if check_zero():
        print(0)
        return

    def run(num_iter):
        freq = [0] * (4 * n)
        zeros = []
        for x in v:
            freq[x] += 1
        
        for i in range(4 * n - 1, -1, -1):
            if freq[i] == 0:
                zeros.append(i)
            while freq[i] > 1 and zeros and zeros[-1] <= i + num_iter:
                freq[i] -= 1
                freq[zeros.pop()] += 1
            if freq[i] > 1:
                if i + num_iter < 4 * n:
                    freq[i + num_iter] += freq[i] - 1
                freq[i] = 1
        
        for x in freq:
            if x > k:
                return False
        return True

    bs = 0
    i = 1 << 20
    while i > 0:
        if not run(bs + i):
            bs += i
        i //= 2
    
    print(bs + 1)

def main():
    t = int(input())
    for _ in range(t):
        solve()

if __name__ == "__main__":
    main()
