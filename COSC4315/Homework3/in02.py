# prints at the bottom
# this testcase is with list and function

def Inc(v):
    v = v + 1
    return v

#initialize
l = [1,2,3]
i = 0

#increment
i = Inc(i)
# get element
element = l[i]

#print
print("i=",i)
print("ith element=",element)
