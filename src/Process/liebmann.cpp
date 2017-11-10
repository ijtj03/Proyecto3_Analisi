//
// Created by av10 on 31/10/17.
//
#include <iostream>
#include <Matrix.hpp>
#include <vector>
#include "liebmann.h"
#include <limits>
#include <cmath>
#include <omp.h>


using namespace anpi;
/**
* Constructor.
* Para instanciar la clase.
* @param pLambda lamba nesesario para sobrerelajacion
* @param up Borde Superior
* @param down Borde inferior
* @param left Borde derecho
* @param left Borde izquierdo
*/
template <typename T>
liebmann<T>::liebmann(T pLambda,edgeNode<T> up,edgeNode<T> down,edgeNode<T> left,edgeNode<T> rigth) {
    // TODO Auto-generated constructor stub
    lambda = pLambda;
    upEdge = up;
    botEdge = down;
    rightEdge=rigth;
    leftEdge =left;

}

template <typename T>
liebmann<T>::~liebmann() {
    // TODO Auto-generated destructor stub
}
/**
* Genera la matriz agregando los bordes
* @param originalMat matriz de dimensiones originales dadas por el usuario
*/
template <typename T>
anpi::Matrix<T> liebmann<T>::generateMat(anpi::Matrix<T> originalMat) {
    Matrix<T> newMat(originalMat.rows()+2,originalMat.cols()+2,T(0));
    int limitX = newMat.rows();
    int limitY = newMat.cols();
    setUpEdge(limitY,newMat);
    setDownEdge(limitY,limitX,newMat);
    setRLEdge(limitY,limitX,newMat);
    return newMat;
}

/**
* Aproxima el valor de las temperaturas en cada uno de los nodos de una matriz
 * utiliza openMP para la optimizacion de los calculos a nivel de procesador
 * realizar la iteracion de las filas y maneja el control del error
* @param matA matriz generada con los bordes incluidos
* @param es error al cual se debe llegar para obtener el resultado de las temperaturas
*/
template <typename T>
Matrix<T> liebmann<T>::solveLiebmannOMP(anpi::Matrix<T> matA, T es) {
    int limit = matA.rows();
    int limitY = matA.cols();
    T error(0);
    std::vector<T> err(4,T(0));
    int  cont(0);
    end=false;
    while (!end) {
        #pragma omp parallel for  num_threads(4)
         for (int i = 1; i < limit-1; ++i) {
             T error = getNodeTem(matA,i,limitY);
             err[omp_get_thread_num()]=error;
         }
        error=getMax(err);
        if(error<es){end=true;}
        ++cont;

    }
    std::cout<<"Error: "<<error<<std::endl;
    std::cout<<"Iterations: "<<cont<<std::endl;
    return matA;
}
/**
* Aproxima el valor de las temperaturas en cada uno de los nodos de una matriz
 * realizar la iteracion de las filas y maneja el control del error
* @param matA matriz generada con los bordes incluidos
* @param es error al cual se debe llegar para obtener el resultado de las temperaturas
*/
template <typename T>
anpi::Matrix<T> liebmann<T>::solveLiebmann(anpi::Matrix<T> matA,T es) {
    int limit = matA.rows();
    int limitY = matA.cols();
    T error(0);
    std::vector<T> err(4,T(0));
    int  cont(0);
    end=false;
    while (!end) {
        for (int i = 1; i < limit-1; ++i) {
             T e = getNodeTem(matA,i,limitY);
             if(error<e){error=e;}
        }
        if(error<es){end=true;}
        ++cont;

    }
    std::cout<<"Error: "<<error<<std::endl;
    std::cout<<"Iterations: "<<cont<<std::endl;
    return matA;
}
/**
* Aproxima el valor de las temperaturas en cada uno de los nodos de una matriz
 * realizar la iteracion de las columnas y maneja el control del error en cada una de las filas
* @param matA matriz generada con los bordes incluidos
* @param node fila en la que se esta evaluando el nodo
* @param limit Cantidad total de columnas
*/
template <typename T>
T liebmann<T>::getNodeTem(anpi::Matrix<T>& matA, int node,int limit) {
    T temp(0);
    T errorTemp(0);

    for (int i = 1; i <limit-1; ++i) {
            temp = matA[node][i+1] + matA[node][i-1]
                            +matA[node+1][i]+matA[node-1][i];
       /* std::cout<<"Node : "<<node<<" i: "<<i
                 <<"\nUp: "<<matA[node-1][i]
                 <<"\nDown: "<<matA[node+1][i]
                 <<"\nRigth: "<<matA[node][i+1]
                 <<"\nLeft: "<<matA[node][i-1]<<std::endl;*/
        temp = temp/4;
            temp = lambda*temp+(1-lambda)*matA[node][i];
            //std::cout<<"Node Temp: "<<temp<<std::endl;
            T err = error(temp,matA[node][i]);
            if(errorTemp<err){errorTemp=err;}
            matA[node][i]=temp;
    }
    return errorTemp;
    }

/**
* Ingresa el borde superior en la matriz dada por el usuario
* @param mat matriz generada con los bordes incluidos
* @param size Cantidad total de columnas
*/

template <typename T>
void liebmann<T>::setUpEdge(int size,anpi::Matrix<T>&mat) {
    T sum = upEdge.getTempDif(size-1);
    for(int i=0;i<size;++i){
        if(i==0){

            mat[0][i]=upEdge.getUp()+leftEdge.getUp();
        }
        else if(i==size-1){
            mat[0][i]=upEdge.getLow()+rightEdge.getUp();
        }
        else{
            mat[0][i] = upEdge.getUp()-(i*sum);
        }
    }
}
/**
* Ingresa el borde inferior en la matriz dada por el usuario
* @param mat matriz generada con los bordes incluidos
* @param size Cantidad total de columnas
* @param rows Cantidad total de filas
*/
template <typename T>
void liebmann<T>::setDownEdge(int size,int rows,anpi::Matrix<T>&mat) {
    T sum = botEdge.getTempDif(size-1);
    int offset = (size-1)*size;
    for(int i=0;i<size;++i){
        if(i==0){
            mat[rows-1][i]=botEdge.getUp()+leftEdge.getLow();
        }
        else if(i==size-1){
            mat[rows-1][i]=botEdge.getLow()+rightEdge.getLow();
        }
        else{
            mat[rows-1][i] = botEdge.getUp()-(i*sum);
        }
    }
}
/**
* Ingresa el borde derecho y el izquierdo en la matriz dada por el usuario
* @param mat matriz generada con los bordes incluidos
* @param sizeY Cantidad total de columnas
* @param sizeX Cantidad total de filas
*/
template <typename T>
void liebmann<T>::setRLEdge(int sizeX,int sizeY,anpi::Matrix<T>&mat) {
    T sumL = leftEdge.getTempDif(sizeY-1);
    T sumR = rightEdge.getTempDif(sizeY-1);
    for (int j = 1; j <sizeY-1; ++j) {
        mat[j][0] = leftEdge.getUp() -(j*sumL);
        mat[j][sizeX-1] = rightEdge.getUp() -(j*sumR);
        }
}
/**
* Imprime la matriz
* @param mat matriz generada con los bordes incluidos

*/
template <typename T>
void liebmann<T>::printMyMat(anpi::Matrix<T> mat) {
    int limitX = mat.rows();
    int limitY = mat.cols();
    for (int i = 0; i <limitX; ++i) {
        std::cout<<"\n";
        for (int j = 0; j <limitY ; ++j) {
            std::cout<<mat[i][j]<<" ";
        }
    }
}
/**
* Obtiene el error entre un valor nuevo y el anterior a este
* @param mat matriz generada con los bordes incluidos
* @param newT Temperatura de nodo nueva
* @param oldT Temperatura de nodo vieja
*/
template <typename T>
T liebmann<T>::error(T newT,T oldT) {
    T error =std::abs((newT-oldT)/newT)*100;
    return error;
}
/**
* Obtiene el error mayor entre cada uno de los hilos
* @param errors vector de errores en cada hilo
*/
template<typename T>
T liebmann<T>::getMax(std::vector<T> errors) {
    T final(0);
    for (int i = 0; i <errors.size() ; ++i) {
        //std::cout<<"Thread: "<<i<<" error: "<<errors[i]<<std::endl;
        if(errors[i]>final){
            final = errors[i];
        }
    }
    return final;
}
/**
* Quita los bordes la matriz para ser impresa y devuelta con sus dimensiones originales
* @param model matriz generada con los bordes incluidos
*/
template <typename T>
anpi::Matrix<T> liebmann<T>::generateFinalMat(anpi::Matrix<T> model) {
    anpi::Matrix<T> res(model.rows()-2,model.cols()-2,T(0));
    int rows = res.rows();
    int cols = res.cols();
    for (int i = 0; i <rows; ++i) {
        for (int j = 0; j <cols; ++j) {
            //if(!(i==0||i==model.rows()-1||j==0||j==model.cols()-1)){
            //res[i-1][j-1]=model[i][j];}
            res[i][j]=model[i+1][j+1];
        }
    }

    return res;
}