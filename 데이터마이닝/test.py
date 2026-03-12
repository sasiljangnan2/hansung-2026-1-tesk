import numpy as np
a = [5, 7, 9]
b = [16, 21 , 24]
x=np.array(a)
y=np.array(b)
mx = np.mean(x)
my = np.mean(y)
print("x의 평균:", mx)
print("y의 평균:", my)
print(x + y)
print(x.__add__(y))