# this testcase if/else, no nesting


x=1
y=2
z=0

# if alone
if x==1:
  z=2

   
# if/else
if y==1:
  z=1
else:
  z=3


# if/else
if z==3:
  x=1
else:
  x=2  


print("x: ",x)
print("y: ",y)
print("z: ",z)
