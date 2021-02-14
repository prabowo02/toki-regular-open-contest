k = int(input())
cur, ans = (1 << 30) - 1, []
while k > 0:
  ans.append(cur)
  cur ^= k & -k
  k ^= k & -k
  ans.append(cur)
  cur ^= (cur & ~k) & -(cur & ~k)

print(len(ans))
print(*ans)
