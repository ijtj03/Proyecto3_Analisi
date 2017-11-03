#include <iostream>
#include <python2.7/Python.h>
#include "Matrix.hpp"
#include "plotQuiver.h"

int main()
{
	//anpi::Matrix<double> ad = {{4,6,8,10,8,6,4},{2,4,6,8,6,4,2},{0,2,4,6,4,2,0},{-2,0,2,4,2,0,-2}};//esta es la matriz  que deberia de salir 
													//basicamente entre mas alto el numero mas calor  hay
	int n = 1000;	
	int max = 100;
	anpi::Matrix<double> ad(n, n, double(0));
	for (int i=0;i!=n;i++){
		for (int j=0;j!=n;j++){
			ad[i][j]=max;
			max = max +10;
		}
		max = ad[i][1];			
	}
	plotpy::PlotQuiver<double> plt;
	plt.initialize(ad);
	plt.plotColor();//esta sirve para imprimir sin las  flechas
	plt.plotQuiver();//esta es para que imprima las flechas
	plt.showPlots();//muestra la grafica
	return 0;

}
