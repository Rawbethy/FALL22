'''# Example 1
square = lambda x: x**2
print(square(4))

# Example 2
close = lambda x, y: abs(x-y) < 3
print(close(2,4))

# Example 3
# Lambda if else used in following syntax <return value> if <condition> else <return value>
fact = lambda x: 1 if x==1 else x * fact(x-1)
print(fact(4)) 
'''
# Write a recursive lambda function expression sum(l) in JavaScript to add all elements in the list. Assume l has ints.
l = [1, 3, 4, 7, 3, 5, 12]
sum = lambda l: l[0] + sum(l[1:]) if l else 0
print(sum(l))
