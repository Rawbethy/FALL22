# this test case tests list plus and getting elements by index and assigment to one list element

listA = [1,1,1,1,1]
listB = [2,2,2,2]
listC = [3,3,3,3,3,3]

sum0 = listA[0] + listB[0] + listC[0]
sum1 = listA[1] + listB[1] + listC[1]
sum2 = listA[2] + listB[2] + listC[2]

#assignment to one list element
listA[0]=0
e=listA[0]

print("sum0: ", sum0)
print("sum1: ", sum1)
print("sum2: ", sum2)
print("e: ", e)


