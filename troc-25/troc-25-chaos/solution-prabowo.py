def solve(N, A):
    lft = 0
    for i in range(N):
        if A[i] > lft:
            rgt, r = 0, 0
            for j in range(i + 1, N):
                rgt += max(0, A[j] - r)
                r += A[j] - r >= 0
            if lft + rgt < A[i]:
                return 'NO'
        lft += A[i] + 1
    return 'YES'


if __name__ == '__main__':
    print(solve(int(input()), [int(s) for s in input().split()]))
