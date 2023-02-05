import sys

def mult_del_split(str, delims) :
    pos = 0
    for i, c in enumerate(str) :
        if c in delims:
            if(str[pos:i] == ""):
                pos = i + 1
                continue
            yield str[pos:i]
            pos = i + 1
    yield str[pos:]

def length(a, i = 0):
    try:
        a[0]
    except IndexError:
        return i
    else:
        return length(a[1:], i+1)

def multiSplit(str, delims, length, i = 0) :
    if(str[i] not in delims and i < length - 1):
        str = multiSplit(str, delims, length, i+1)
    else:
        if(i != length - 1):
            str = str.replace(str[i], " ")
            str = multiSplit(str, delims, length, i+1)
    return str

def merge(a, b):
    if(length(a) == 0):
        return b
    elif(length(b) == 0):
        return a
    elif (a[0] < b[0]):
        return [a[0]] + merge(a[1:], b)
    else:
        return [b[0]] + merge(a, b[1:])

def mergesort(a):
    if(length(a) < 2):
        return a
    else:
        m = length(a) // 2
        return merge(mergesort(a[:m]), mergesort(a[m:]))

def noRepeats(a):
    if(length(a) == 1):
        return [a[0]]
    elif(a[0] in a[1:]):
        return noRepeats(a[1:])
    else:
        return [a[0]] + noRepeats(a[1:])

def freq(a, i = 1):
    len = length(a) - 1
    if(len == 0):
        return [i]
    elif(a[len] in a[:len]):
        return freq(a[:len], i+1)
    else:
        return freq(a[:len]) + [i]

def findMax(a, len, ind = 1, maxInd = 0, ignore = []):
    if(ind in ignore):
        if(ind+1 > len):
            return maxInd
        else:
            return findMax(a, len, ind+1, maxInd, ignore)
    if(maxInd in ignore):
        if(maxInd+1 > len):
            return ind
        else:
            return findMax(a, len, ind, maxInd+1, ignore)
    if(ind == len):
        if(a[ind] > a[maxInd]):
            return ind
        else:
            return maxInd
    else:
        if(a[ind] > a[maxInd]):
            return findMax(a, len, ind+1, ind, ignore)
        else:
            return findMax(a, len, ind+1, maxInd, ignore)

def printK(a, b, k, ignore):
    if(k == 0):
        return 
    else:
        if(length(b) < k):
            return printK(a, b, k-1, ignore)
        maxInd = findMax(a, length(a)-1, 1, 0, ignore)
        w.write(str(b[maxInd]) + " " + str(a[maxInd]) + "\n")
        ignore += [maxInd]
        return printK(a, b, k-1, ignore)

                  
stringArg = sys.argv[1]
splitArgs = list(mult_del_split(stringArg, ";="))
k = int(splitArgs[1])

f = open(splitArgs[3], "r")
w = open(splitArgs[5], "w")
delims = " +;,\s+\n+\t+!@#$%^\"\'&*()_-=?/:><abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
numbers = f.read()
len = length(numbers)
splitStr = multiSplit(numbers, delims, len)
splitStr = splitStr.split()
splitStr = list(filter(lambda x: x != ".", splitStr))
splitNums = list(map(lambda x: float(x) if "." in x else int(x) , splitStr))

realNums = list(filter(lambda x: x%1 != 0, splitNums))
intNums = list(filter(lambda x: x%1==0, splitNums))

realNumsSort = mergesort(realNums)
intNumsSort = mergesort(intNums)

noReReal = noRepeats(realNumsSort)
noReInt = noRepeats(intNumsSort)


freqInt = freq(intNumsSort)
freqReal = freq(realNumsSort)
w.write("integer:\n")
printK(freqInt, noReInt, int(k), ignore = [])
w.write("real:\n")
printK(freqReal, noReReal, int(k), ignore = [])
w.close()






