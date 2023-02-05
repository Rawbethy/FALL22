#this test case: 
#  list operator [] + 
#  functions that witrh one or two paramenters 
#


#Return list at index
def getElement(l,index):
    element = l[index]
    return element

#Increment val
def inc(v):
    v = v + 1
    return v

l1 = [1,2,3,4,5,6]
i = 0
l2= [10,11,12]

# pass variable
a = getElement(l1,i)
# pass value
b = getElement(l2,1)
i= inc(i)
i= inc(i)
# chained
j= inc(i)
c= getElement(l1,j)

l3=[0,0,0,0,0]
l3[0]=a
l3[1]=b
l3[2]=c

print("l1: ",l1)
print("l2: ",l2)
print("l3: ",l3)
