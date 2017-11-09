#include <iostream>
#include <python2.7/Python.h>
#include <chrono>
#include "Matrix.hpp"
#include "plotQuiver.h"
#include "edgeNode.cpp"
#include "liebmann.cpp"
using namespace anpi;


int main()
{
													//basicamente entre mas alto el numero mas calor  hay
    //Bordes con rangos de temperaruta
    edgeNode<double> up(100,100);
    edgeNode<double> down(0,0);
    edgeNode<double> r(50,50);
    edgeNode<double> l(75,75);

    //tamano de la placa metalica
    Matrix<double> mat(512,512);
    liebmann<double> lieb(1.5,up,down,l,r);
    Matrix<double> a;
    a= lieb.generateMat(mat);
    std::cout<<"Computing...."<<std::endl;
    //lieb.printMyMat(a);
    auto t_startOMP = std::chrono::high_resolution_clock::now();
    lieb.solveLiebmannOMP(a,1);
    auto t_endOMP = std::chrono::high_resolution_clock::now();
    double timeOMP = double(std::chrono::duration<double, std::milli>(t_endOMP - t_startOMP).count()) / 1000;
    //lieb.printMyMat(a);
    std::cout<<"time OMP "<<timeOMP<<std::endl;
    a = lieb.generateFinalMat(a);
    plotpy::PlotQuiver<double> plt;
    plt.initialize(a);
    plt.plotColor();//esta sirve para imprimir sin las  flechas
    plt.plotQuiver();//esta es para que imprima las flechas
    plt.showPlots();//muestra la grafica
	return 0;

}
