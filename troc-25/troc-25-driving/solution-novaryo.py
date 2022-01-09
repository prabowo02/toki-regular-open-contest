N, F, D = map(int, input().split())
if N < F:
  print('NO')
  exit(0)

mn = F * (F + 1) // 2
mx = 0
spd_now = 0
for i in range(0, N):
  if N - i - 1 >= spd_now + 1 - F:
    spd_now += 1
  elif N - i - 1 < spd_now - F:
    spd_now -= 1
  mx += spd_now

if mn <= D <= mx:
  print('YES')
else:
  print('NO')