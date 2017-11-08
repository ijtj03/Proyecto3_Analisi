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
	//anpi::Matrix<double> ad = {{4,6,8,10,8,6,4},{2,4,6,8,6,4,2},{0,2,4,6,4,2,0},{-2,0,2,4,2,0,-2}};//esta es la matriz  que deberia de salir
													//basicamente entre mas alto el numero mas calor  hay

    edgeNode<double> up(1000,1000);
    edgeNode<double> down(300,300);
    edgeNode<double> r(800,800);
    edgeNode<double> l(900,800);
    std::vector<double> time;
    Matrix<double> mat(23,23);
    liebmann<double> lieb(1.5,up,down,l,r);
    Matrix<double> a;
    a= lieb.generateMat(mat);
    std::cout<<"Matrix Generated---------------------"<<std::endl;
    //lieb.printMyMat(a);
    auto t_start = std::chrono::high_resolution_clock::now();
    lieb.solveLiebmann(a);
    auto t_end = std::chrono::high_resolution_clock::now();
    time.push_back(double(std::chrono::duration<double, std::milli>(t_end - t_start).count()) / 1000);
    std::cout<<"time "<<time[0]<<std::endl;
    a = lieb.generateFinalMat(mat);
    //lieb.printMyMat(a);
    plotpy::PlotQuiver<double> plt;
    plt.initialize(a);
    plt.plotColor();//esta sirve para imprimir sin las  flechas
    plt.plotQuiver();//esta es para que imprima las flechas
    plt.showPlots();//muestra la grafica
	return 0;

}
