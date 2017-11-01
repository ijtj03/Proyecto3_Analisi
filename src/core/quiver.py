import numpy as np
import pylab as plt

def getAuxMats(Z):
	k = 1
	print(n)
	delX = 1
	delY = 1
	dx = np.linspace(0,(len(Z[0])-1),len(Z[0]))	
	dy = np.linspace(0,(len(Z)-1),len(Z))	
	X,Y = np.meshgrid(dx,dy)
	u = np.zeros((len(Z),len(Z[0])))
	v = np.zeros((len(Z),len(Z[0])))
	a,b=0,0
	for x in range(len(Z)):
		for y in range(len(Z[0])):
			if(x!=0 and x!=len(Z)-1 and y!=0 and y!=len(Z[0])-1):
				v[x][y]= k*(Z[x+1][y]-Z[x-1][y])/(2*delX)
				u[x][y]= -k*(Z[x][y+1]-Z[x][y-1])/(2*delY)		
			else:
				v[x][y]= k/2*delX
				u[x][y]= -k/2*delY
			y+=5

	plt.imshow(z)
	plt.colorbar()
	plt.quiver(X,Y,u,v,Z,width=.01,linewidth=1)	
	plt.colorbar() 
	plt.show()

n = 10
z = np.zeros((n,n))
nMin = 0
for x in range(n):
	for y in range(n):
		nMin-=10	
		z[x][y] =nMin
	nMin = z[x][1] 
#print(z)		
getAuxMats(z)
