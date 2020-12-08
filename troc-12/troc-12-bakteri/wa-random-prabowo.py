import random


def solve(n, m, k):
    ans = [['.' for j in range(m)] for i in range(n)]

    for i in range(min(n, m)):
        ans[i][random.randrange(min(n, m))] = 'X'
        k -= 1

    if n < m:
        for i in range(m, n, -2):
            ans[random.randrange(n)][i-1] = 'X'
            k -= 1
    elif n > m:
        for i in range(n, m, -2):
            ans[i-1][random.randrange(m)] = 'X'
            k -= 1

    if k < 0:
        return print('TIDAK')

    for i in range(n):
        for j in range(m):
            if k > 0 and ans[i][j] == '.':
                ans[i][j] = 'X'
                k -= 1

    print('YA')
    print('\n'.join([''.join(row) for row in ans]))


if __name__ == '__main__':
    solve(*[int(s) for s in input().split()])
