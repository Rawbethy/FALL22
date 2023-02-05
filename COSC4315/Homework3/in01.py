# change: simple values 0,1,2 var name A,B,C,D
# this test case is with repeated print statement


A = 0
B = 1

C = A + B
D = C + A  
E = D + B

# repeated
print("C: ",C)
print("D: ",D)
print("E: ",E)
print("C: ",C)
print("D: ",D)
print("E: ",E)
print("C: ",C)
print("D: ",D)
print("E: ",E)
