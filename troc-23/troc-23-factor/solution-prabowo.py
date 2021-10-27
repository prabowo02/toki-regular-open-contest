n = int(input())
print('YES' if len([i for i in range(n) if n % (i + 1) == 0]) == 5 else 'NO')
