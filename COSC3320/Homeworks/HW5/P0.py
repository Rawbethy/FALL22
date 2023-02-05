import sys
size = int(input())
palString = input()
if(len(palString) != size):
    print("Input size and string size do not match")
    exit(0)

memoized = [[False for i in range(size)] for j in range(size)]
smallestPal = [sys.maxsize for i in range(size+1)]
smallestPal[size] = 0

for i in range (size-1,-1,-1):
    memoized[i][i-1] = True
    memoized[i][i] = True
    for j in range(i+1,size):
        if palString[i] == palString[j]:
            memoized[i][j] = memoized[i+1][j-1]
        else:
            memoized[i][j] = False

for i in range(size-1,-1,-1):
    for j in range(i, size):
        if(memoized[i][j] == True):
            smallestPal[i] = min(smallestPal[i], 1 + smallestPal[j+1])

print(smallestPal[0])
