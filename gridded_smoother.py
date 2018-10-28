#cwh, march 18

import numpy as np
import matplotlib.pyplot as plt
from scipy.spatial import distance as dist

m = 20
n = 25
dx = 1.0
x = np.arange(0,m,dx) #lon grid points
y = np.arange(0,m,dx) #lat grid points
size = len(x)*len(y)    #voxel space
a = np.random.rand(n)*(m-1)   #data lon
b = np.random.rand(n)*(m-1)   #data lat
amp = np.random.exponential(2,n) #amplitude


w = []  #weights
p = np.zeros((size,3))
r = 0 #row tracker

for i in range(len(x)): #loop over x
    for j in range(len(y)): #loop over y
        for k in range(len(a)): #loop over data
            d = dist.euclidean((x[i],y[j]),(a[k],b[k])) #L2 distance
            ww = 1/np.square(d) #weighting function
            if d > dx*2.0:
                ww = 0 #set weight above a certain distance to 0
            w.append(ww) #all weights for this spatial point
        s = np.dot(w,amp) #find the weighted sum of all data at given point
        smooth = 0  #set default to zero
        if np.sum(w) > 0: #update to smoothed average if data are close
            smooth = s/np.sum(w) #don't want to divide by 0
        p[r,0] = x[i] #xcoord
        p[r,1] = y[j] #ycoord
        p[r,2] = smooth #new smoothed value in box x_i, y_j
        r = r + 1 #update row after looping thru x, y
        w = [] #clear for next loop
        s = [] #ditto
        dd = [] #ditto

x1 = []
y1 = []
z1 = []
x0 = []
y0 = []
z0 = []

for i in range(len(p[:,0])):
    if p[i,2]>0:
        x1.append(p[i,0])
        y1.append(p[i,1])
        z1.append(p[i,2])
    if p[i,2]==0:
        x0.append(p[i,0])
        y0.append(p[i,1])
        z0.append(p[i,2])

color = 'jet'
plt.scatter(x0,y0,c='k',marker='+')
plt.scatter(x1,y1,c=z1,marker='o',cmap=color)
plt.scatter(a,b,c=amp,marker='*',s=200,cmap=color)  #plot datapoints
plt.colorbar()

plt.show()
