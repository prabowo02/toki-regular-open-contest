s = int('1' * 100, 5) - int(input())
can = True
while s > 0:
    if s % 5 > 2:
        can = False
    s //= 5

print('YES' if can else 'NO')
