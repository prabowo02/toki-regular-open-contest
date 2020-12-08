# Author   : rama_pang
# Problem  : troc-12-dunia
# Time     : O(1)
# Memory   : O(1)

from sys import stdin, stdout

def main():
  A, X = [int(x) for x in stdin.readline().split()]
  stdout.write(str(X // A) + ' ' + str(X % A) + '\n')

if __name__ == '__main__':
  main()