def ask(*args):
    print('?', *args, flush=True)
    return int(input())

def cc(l, r, d, u):
    return ask(l, r, d, u) - (r - l + 1) * (u - d + 1)

def search(N, lft, rgt):
    l, r = 1, N
    while l < r:
        mid = (l + r) // 2
        if lft(mid) + 1 == rgt(mid):
            r = mid
        else:
            l = mid + 1
    return l

N = int(input())

print('!', 
    search(N, lft=lambda m: cc(1, m, 1, N), rgt=lambda m: cc(m + 1, N, 1, N)),
    search(N, lft=lambda m: cc(1, N, 1, m), rgt=lambda m: cc(1, N, m + 1, N)))
