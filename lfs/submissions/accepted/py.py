# (almost) mechanical translation of dario.cpp into Python.

def solve():
    last_occ = [[-1] * 1000010 for _ in range(26)]
    cnt = [[0] * 1000010 for _ in range(26)]
    last_diff = [-1] * 1000010

    n, q = map(int, input().split())
    s = [ord(x) - ord('a') for x in input().strip()]

    last_occ[s[0]][0] = 0
    for i in range(1, n):
        for c in range(26):
            last_occ[c][i] = last_occ[c][i-1]
        last_occ[s[i]][i] = i

    for i in range(n):
        for c in range(26):
            cnt[c][i+1] = cnt[c][i]
        cnt[s[i]][i+1] += 1

    for i in range(n - 1):
        c = s[i]
        prev_occ = -1 if i == 0 else last_occ[c][i-1]
        if prev_occ != -1:
            if s[prev_occ+1] != s[i+1]:
                last_diff[i] = prev_occ
            else:
                last_diff[i] = last_diff[prev_occ]

    freq = [0] * 26
    good = [False] * 26
    follow = [-1] * 26
    depth = [0] * 26

    def dfs(c):
        if c == -1:
            return 0
        if depth[c] == 0:
            depth[c] = 1 + dfs(follow[c])
        return depth[c]

    for _ in range(q):
        l, r = map(int, input().split())
        l -= 1
        r -= 1
        max_freq = 0
        for c in range(26):
            f = cnt[c][r+1] - cnt[c][l]
            freq[c] = f
            max_freq = max(max_freq, f)
        
        for c in range(26):
            good[c] = freq[c] == max_freq

        end_c = s[r]
        for c in range(26):
            if c == end_c or not good[c]:
                follow[c] = -1
            else:
                lo_c = last_occ[c][r]
                pos = last_diff[lo_c]
                if pos >= l:
                    follow[c] = -1
                else:
                    maybe = s[lo_c + 1]
                    follow[c] = maybe if good[maybe] else -1

        for c in range(26):
            depth[c] = 0
        
        ans = 0
        for c in range(26):
            if depth[c] == 0 and good[c]:
                ans = max(ans, dfs(c))
        
        print(ans)

solve()
