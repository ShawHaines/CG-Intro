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
dphi=2*math.pi/slices
r=np.array([x,y]).reshape((2,1))
R=eulerMatrix(theta)
A=np.array([[math.cos(dphi),-a/b*math.sin(dphi)],[b/a*math.sin(dphi),math.cos(dphi)]])
# be careful with the transpose
M=np.dot(R,np.dot(A,R.T))

pointList=[]
plt.scatter(*r)
for phi in np.linspace(0,2*math.pi,slices):
    r=np.dot(M,r)
    pointList.append(np.round(r))
    plt.scatter(*pointList[-1])
plt.show()
# print(pointList)
# print(M)

# Another version:

# r=np.array([a,0]).reshape((2,1))
# plt.scatter(*np.dot(R,r))
# for phi in np.linspace(0,2*math.pi,slices):
#     r=np.dot(A,r)
#     plt.scatter(*np.dot(R,r))
# plt.show()

# draw a filled a polygon.

# def fill(pointCloud):
#     """
#     pass in a N*2 point array as an ordered polygon.
#     """
#     for y in range(np.min(pointCloud(:,1)),np.max(pointCloud(:,1))+1):
#         for x in activeRange()
    