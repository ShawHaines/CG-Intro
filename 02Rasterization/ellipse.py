import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
import math

def eulerMatrix(theta):
    return np.array([[math.cos(theta),-math.sin(theta)],[math.sin(theta),math.cos(theta)]])

a,b,theta=[float(x) for x in input().split()]
slices=100
x=math.cos(theta)*a
y=math.sin(theta)*a
r=np.array([x,y]).reshape((2,1))
R=eulerMatrix(theta)
A=np.array([[0,-a/b],[b/a,0]])
M=np.dot(R,np.dot(A,R.T))

pointList=[]
dphi=2*math.pi/slices
for phi in np.linspace(0,2*math.pi,slices):
    dr=np.dot(M,r)*dphi
    r+=dr
    pointList.append(r)
    plt.scatter(*r)
plt.show()
# print(M)