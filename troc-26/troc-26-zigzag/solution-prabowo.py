N = int(input())
B = list(map(int, input().split()))

def solve(N, B):
    s, cur = sum(B), 0
    for b in B:
        if cur < s // 2 and b > s // 2:
            return False
        cur += b
    return True

print('YES' if solve(N, B) else 'NO')
