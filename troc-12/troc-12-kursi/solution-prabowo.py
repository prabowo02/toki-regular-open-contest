import sys


if __name__ == '__main__':
    input()
    for line in sys.stdin.readlines():
        x, y = line.split()
        x = int(x); y = int(y)

        if x - y & 3:
            print(x + y)
        elif x == y:
            print(x + y + (x>0)*2)
        else:
            ctz = 2 << len(bin(x-y>>2)) - len(bin(x-y>>2).rstrip('0'))
            m = y & ((ctz << 1) - 1)
            print(x + y + (not (m == 0 or m & ctz)) * 2)
