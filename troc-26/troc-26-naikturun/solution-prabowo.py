N, M = [int(s) for s in input().split()]
A = [[int(s) for s in input().split()] for _ in range(N)]

odd, even, unknown = 0, 0, -1
for i in range(N):
    for j in range(M):
        if A[i][j] == -1:
            unknown = (i + j) % 2
            continue
        if (i + j) % 2:
            odd += A[i][j]
        else:
            even += A[i][j]

ans = even - odd if unknown == 1 else odd - even
if ans < 0:
    print('NO')
else:
    print('YES')
    print(ans)
