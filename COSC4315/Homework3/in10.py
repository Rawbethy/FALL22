# this testcase tests list operator
# out of bound index in list, element n+1


#initialize list
listA = [1,2,3,4,5]
ListB = [6,7,8,9,10]
listC = []

#Increment x
i = 0 
v = 100

listC = listA + ListB
listC[i] = listC[i] + v

# out of bound, runtime error, py starts at listC[0]
i= 10
listC[i] = 0

print(listC)

