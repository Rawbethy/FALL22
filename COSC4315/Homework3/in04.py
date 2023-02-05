# test: functions and nested if/else
#

def inc(x):
  x=x+1
  return x


# notice one variable returned to make it simple
def add(x,y):
 z=x+y
 return z


x=4
y=2
z=3
b=inc(x)
c=add(x,y)

if x==1:
  a=2
else:
  if y==3:
    a=1
  else:
    a=3

print("a: ",a)
print("b: ",b)
print("c: ",c)

