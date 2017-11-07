import numpy as np
import pylab as plt

def getAuxMats(Z):
	k = 1
	delX = 1
	delY = 1
	if((len(Z[0])+len(Z))//(2)>=10):
		n=(len(Z[0])+len(Z))//(2*10)
	else:
		n=1
	dx = np.linspace(0,(len(Z[0])-n),len(Z[0])//n)	
	dy = np.linspace(0,(len(Z)-n),len(Z)//n)	
	X,Y = np.meshgrid(dx,dy)
	u = np.zeros((len(X),len(X[0])))
	v = np.zeros((len(X),len(X[0])))
	a,b=0,0
	for x in range(len(X)):
		for y in range(len(X[0])):
			if(a!=0 and a!=len(Z)-1 and b!=0 and b!=len(Z[0])-1):
				v[x][y]= k*(Z[a+1][b]-Z[a-1][b])/(2*delX)
				u[x][y]= -k*(Z[a][b+1]-Z[a][b-1])/(2*delY)		
			else:
				v[x][y]= 0
				u[x][y]= 0
			b+=n
		a+=n
		b=0
	return [X,Y,u,v]
	plt.imshow(z)
	plt.colorbar()
	plt.quiver(X,Y,u,v,width=.01,linewidth=1)	
	plt.show()
	

n = 500
z = np.zeros((n,n))
nMin = 0
for x in range(n):
	for y in range(n):	
		z[x][y] =nMin
	nMin+=10
#print(z)		
getAuxMats(z)
