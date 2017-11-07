#include <iostream>
#include <python2.7/Python.h>
#include "Matrix.hpp"
#include "plotQuiver.h"
#include "edgeNode.cpp"
#include "liebmann.cpp"
using namespace anpi;


int main()
{
	/*anpi::Matrix<double> ad = {{4,6,8,10,8,6,4},{2,4,6,8,6,4,2},{0,2,4,6,4,2,0},{-2,0,2,4,2,0,-2}};//esta es la matriz  que deberia de salir
													//basicamente entre mas alto el numero mas calor  hay
	/*plotpy::PlotQuiver<double> plt;
	plt.initialize(ad);
	plt.plotColor();//esta sirve para imprimir sin las  flechas
	plt.plotQuiver();//esta es para que imprima las flechas
	plt.showPlots();//muestra la grafica*/
    edgeNode<double> up(100,100);
    edgeNode<double> down(0,0);
    edgeNode<double> r(50,50);
    edgeNode<double> l(75,75);

    Matrix<double> mat(5,5);
    liebmann<double> lieb(1.5,down,up,l,r);
    Matrix<double> a;
    a= lieb.generateMat(mat);
    //lieb.printMyMat(a);
    lieb.solveLiebmann(a);

	return 0;

}
