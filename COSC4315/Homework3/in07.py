# this testcase is with nested if/else and list operators head/tail
#

listX1 = [1,0,0,0]
listX2 = [0,2,0,0]
listX3 = [0,0,3,0]
listX4 = [0,0,0,4]
headX1=  listX1[0]
tailX1 = listX1[1:]

val1 = 0
val2 = 0
val3 = 0
val4 = 0

if headX1 == 1:
    if listX2[1] == 2:
        val1 = 10
    else:
        val2 = 20
else:
    if listX2[1] == 2:
        val1 = 1
    else:
        val2 = 2

if listX2[2] == 3:
    if listX2[3] == 4:
        val3 = 10
    else:
        val4 = 20
else:
    if listX2[3] == 4:
        val3 = 1
    else:
        val4 = 2

print(val1)
print(val2)
print(val3)
print(val4)
