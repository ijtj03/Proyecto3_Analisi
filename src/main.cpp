#include <iostream>
#include <python2.7/Python.h>
#include "Matrix.hpp"
#include "plotQuiver.h"
#include "edgeNode.cpp"
#include "liebmann.cpp"
using namespace anpi;


int main()
{
	//anpi::Matrix<double> ad = {{4,6,8,10,8,6,4},{2,4,6,8,6,4,2},{0,2,4,6,4,2,0},{-2,0,2,4,2,0,-2}};//esta es la matriz  que deberia de salir
													//basicamente entre mas alto el numero mas calor  hay

    edgeNode<double> up(1000,1000);
    edgeNode<double> down(300,300);
    edgeNode<double> r(800,0);
    edgeNode<double> l(900,100);

    Matrix<double> mat(20,20);
    liebmann<double> lieb(1.5,down,up,l,r);
    Matrix<double> a;
    a= lieb.generateMat(mat);
    //lieb.printMyMat(a);
    lieb.solveLiebmann(a);
    a = lieb.generateFinalMat(mat);
    lieb.printMyMat(a);

    plotpy::PlotQuiver<double> plt;
    plt.initialize(a);
    plt.plotColor();//esta sirve para imprimir sin las  flechas
    plt.plotQuiver();//esta es para que imprima las flechas
    plt.showPlots();//muestra la grafica
	return 0;

}
