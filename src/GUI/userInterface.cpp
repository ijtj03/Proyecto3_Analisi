//
// Created by av10 on 09/11/17.
//

#include "userInterface.h"
using namespace std;
userInterface::userInterface() {

}

void userInterface::init() {

        int option(0);
        while(true){
            int rows(0);
            int cols(0);
            cout<<"Temperature Analisis Program"<<"\n\n";
            cout<<"Enter an integer number of rows"<<"\n";
            cin>>rows;
            cout<<"\nEnter an integer number of cols"<<"\n";
            cin>>cols;
            setUpMat(rows,cols);
        }

}
void userInterface::setUpMat(int rows, int cols) {
    Matrix<double> mat(rows,cols);
    liebmann<double> lieb(1.5,
                          getEdge("Top"),
                          getEdge("Down"),
                          getEdge("Rigth"),
                          getEdge("Left"));
    Matrix<double> a;
    a= lieb.generateMat(mat);
    calcMat(a,lieb);
}

edgeNode<double> userInterface::getEdge(string edge) {
    double max(0);
    double min(0);
    cout<<"To use isolated Edges, you must enter max=0 and min=0"<<endl;
    cout<<"Enter "<<edge<<" Edge Max"<<"\n";
    cin>>max;
    cout<<"Enter "<<edge<<" Edge Min"<<"\n";
    cin>>min;
    edgeNode<double> up(max,min);
    return up;
}

void userInterface::calcMat(anpi::Matrix<double> matA,liebmann<double> lieb) {
    double error(100);
    int option(0);
    cout<<"Enter a porcentage error higher than 0 and lower than 100"<<endl;
    //cout<<"A high error will affect the graph details"<<endl;
    cout<<"Enter Error"<<"\n";
    cin>>error;
    cout<<"Menu:\n"<<"1.With Optimization\n"<<"2.With Out Optimization\n"<<"3.exit\n";
    cout<<"Enter an option number"<<"\n";
    cin>>option;
    if(option==1){
        cout<<"Computing...."<<"\n";
        auto t_startOMP = std::chrono::high_resolution_clock::now();
        matA =lieb.solveLiebmannOMP(matA,error);
        auto t_endOMP = std::chrono::high_resolution_clock::now();
        double timeOMP = double(std::chrono::duration<double, std::milli>(t_endOMP - t_startOMP).count()) / 1000;
        std::cout<<"time OMP: "<<timeOMP<<std::endl;
        graphMat(matA,lieb);
    }
    else if(option==2){
        cout<<"Computing...."<<"\n";
        auto t_start = std::chrono::high_resolution_clock::now();
        matA=lieb.solveLiebmann(matA,error);
        auto t_end = std::chrono::high_resolution_clock::now();
        double time = double(std::chrono::duration<double, std::milli>(t_end - t_start).count()) / 1000;
        std::cout<<"time: "<<time<<std::endl;
        graphMat(matA,lieb);
    }
}

void userInterface::graphMat(anpi::Matrix<double> matA,liebmann<double> lieb) {\
    matA = lieb.generateFinalMat(matA);
    int option(0);
    plotpy::PlotQuiver<double> plt;
    plt.initialize(matA);
    cout<<"Menu:\n"<<"1.Graph Vector and Color\n"<<"2.Graph Color\n"<<"3.exit\n";
    cout<<"Enter an option number"<<"\n";
    cin>>option;
    if(option==1){
        plt.plotColor();//esta sirve para imprimir sin las  flechas
        plt.plotQuiver();//esta es para que imprima las flechas
        plt.showPlots();//muestra la grafica
    }
    else if(option==2){
        plt.plotColor();//esta sirve para imprimir sin las  flechas
        plt.showPlots();//muestra la grafica
    }

}