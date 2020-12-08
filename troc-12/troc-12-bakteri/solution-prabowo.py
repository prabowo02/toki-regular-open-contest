import random


def solve(n, m, k):
    ans = [['.' for j in range(m)] for i in range(n)]

    x, y = n-1, m-1
    ans[x][y] = 'X'
    k -= 1

    while x + y >= 2:
        for i in range(2):
            while True:
                r = random.randrange(2)
                if r == 0 and x > 0:
                    x -= 1
                    break
                if r == 1 and y > 0:
                    y -= 1
                    break

        ans[x][y] = 'X'
        k -= 1

    if ans[0][0] != 'X':
        ans[0][0] = 'X'
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
