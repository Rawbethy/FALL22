# this test case is with syntax error, missing : in function def
# we need another one with missing ( or )

def add(x,y)
    z= x+y
    return z

#Return list at index
def getElement(data,index):
    element = data[index]
    return element


data = [100,99,88,77]

a = getElement(data,0)
b = getElement(data,1)
c = add(a,b)
print(c)
