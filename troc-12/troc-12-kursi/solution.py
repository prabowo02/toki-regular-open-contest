#Runs in under 7 seconds on Patrick's computer
import sys;
def between(a, b, c):
	return (a<b and b<c) or (a>b and b>c)
t=int(input())
for i in range(t):
	x, y=map(int, sys.stdin.readline().split());
	x1, x2, x3=y1, y2, y3=0, 1073741824, 2147483648
	for j in range(30):
		if(between((x1+x2)//2, x, (x2+x3)//2) and between((y1+y2)//2, y, (y2+y3)//2)):
			x1=(x1+x2)//2
			x3=(x3+x2)//2
			y1=(y1+y2)//2
			y3=(y3+y2)//2
		elif(between(x2, x, x3) and between(y1, y, y2)):
			x1=x3
			x3=x2
			y3=y2
		elif(between(x1, x, x2) and between(y2, y, y3)):
			x3=x2
			y1=y3
			y3=y2
		elif(between(x1, x, x2) and between(y1, y, y2)):
			x3=x2
			y3=y2
		else:
			break
		x2=(x1+x3)//2
		y2=(y1+y3)//2
	if(x1+1==x2 and y1+1==y2):
		print(x+y+2)
	else:
		print(x+y)
