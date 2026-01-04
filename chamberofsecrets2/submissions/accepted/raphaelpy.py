# Mechanical translation of raphael.cpp.

def solve(blocks):
    n = len(blocks)
    m = len(blocks[0])
    
    if n % 2 == 0:
        res = []
        seen = set()
        for b in blocks:
            tb = tuple(b)
            if tb not in seen:
                seen.add(tb)
                res.extend(b)
        return res

    second_half_to_index = {}
    for i in range(n):
        second = tuple(blocks[i][m // 2:])
        second_half_to_index[second] = i
        
    for middle in range(n):
        used = set()
        res = []
        cur_block = blocks[middle]
        
        for i in range(n):
            first = tuple(cur_block[:m // 2])
            if first not in second_half_to_index:
                break
            
            next_idx = second_half_to_index[first]
            if next_idx in used:
                break
                
            used.add(next_idx)
            cur_block = blocks[next_idx]
            if i % 2 == 1:
                res.append(blocks[next_idx])
        
        if len(used) != n:
            continue
            
        res.reverse()
        flattened_res = []
        for b in res:
            flattened_res.extend(b)
        
        flattened_res.extend(blocks[middle][:m // 2])
        return flattened_res
    return []

t = int(input())
for _ in range(t):
    n, m = map(int, input().split())
    blocks = []
    for i in range(n):
        blocks.append(list(map(int, input().split())))
    
    v = solve(blocks)
    print(' '.join([str(x) for x in v]))
