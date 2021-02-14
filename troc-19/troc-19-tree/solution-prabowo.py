N = int(input())
if N == 2:
    u, v = input().split()
    print('YES' if u != v else 'NO')
else:
    print('YES' if '1' in input() else 'NO')
