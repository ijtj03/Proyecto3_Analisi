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

template <typename T>
anpi::Matrix<T> liebmann<T>::generateMat(anpi::Matrix<T> originalMat) {
    int limitX = originalMat.rows();
    int limitY = originalMat.cols();
    std::vector<T> vector(limitX*limitY,T(0));
    std::vector<T> vectorOld(limitX*limitY,T(0));
    vectorX = vector;
    vectorXold = vectorOld;
    setUpEdge(limitY);
    setDownEdge(limitY);
    setRLEdge(limitY,limitX);
    printX();
    Matrix<T> newMat(limitX*limitY,limitX*limitY,T(0));
    for(int i= 0; i<limitX*limitY;++i){
        fillMat(newMat,i,limitX,limitY);
    }
    return newMat;
}

template<typename T>
int liebmann<T>::identifyNode(int node, int maxX, int maxY) {
    if(node==0){return 1;}
    else if(node==maxY-1){return 2;}
    else if(node==(maxX-1)*maxY){return 3;}
    else if(node== (maxX*maxY)-1){return 4;}
    else if(node<maxY){return 5;}
    else if(node>(maxX-1)*maxY){return 6;}
    else if(node%maxY==0){return 7;}
    else if((node-maxY+1)%maxY==0){return 8;}
    else{return 9;}
}

template<typename T>
void liebmann<T>::fillMat(anpi::Matrix<T> &matA,int nodeX,int maxX,int maxY) {
    int id = identifyNode(nodeX,maxX,maxY);
    matA[nodeX][nodeX]=4;
    //std::cout<<"node id "<<id<<std::endl;
    switch(id){
        case 1:
            matA[nodeX][1]=-1;
            matA[nodeX][nodeX+maxY]=-1;
            break;
        case 2:
            matA[nodeX][nodeX-1]=-1;
            matA[nodeX][nodeX+maxY]=-1;
            break;
        case 3:
            matA[nodeX][nodeX+1]=-1;
            matA[nodeX][nodeX-maxY]=-1;
            break;
        case 4:
            matA[nodeX][nodeX-1]=-1;
            matA[nodeX][nodeX-maxY]=-1;
            break;
        case 5:
            matA[nodeX][nodeX+1]=-1;
            matA[nodeX][nodeX-1]=-1;
            matA[nodeX][nodeX+maxY]=-1;
            break;
        case 6:
            matA[nodeX][nodeX+1]=-1;
            matA[nodeX][nodeX-1]=-1;
            matA[nodeX][nodeX-maxY]=-1;
            break;
        case 7:
            matA[nodeX][nodeX+maxY]=-1;
            matA[nodeX][nodeX-maxY]=-1;
            matA[nodeX][nodeX+1]=-1;
            break;
        case 8:
            matA[nodeX][nodeX+maxY]=-1;
            matA[nodeX][nodeX-maxY]=-1;
            matA[nodeX][nodeX-1]=-1;
            break;
        case 9:
            matA[nodeX][nodeX+maxY]=-1;
            matA[nodeX][nodeX-maxY]=-1;
            matA[nodeX][nodeX-1]=-1;
            matA[nodeX][nodeX+1]=-1;
            break;
    }

}

template <typename T>
void liebmann<T>::solveLiebmann(anpi::Matrix<T> matA) {
    int limit = matA.rows();
    T es = 1;

    //vectorXold = vector;

    int  cont(0);
    while (cont<3) {
        #pragma omp parallel for
        for (int i = 1; i < limit-1; ++i) {
            if (cont > 0) {
                vectorXold[i] = vectorX[i]; }
            vectorX[i] = (T(-1)*getNodeTem(matA, i, limit));
        }
        printX();
        cont++;
        std::cout<<"\nnumber count "<<cont<<"\n"<<std::endl;

    }
    printX();
}

template <typename T>
T liebmann<T>::getNodeTem(anpi::Matrix<T> matA, int node,int limit) {
    T temp(0);

    for (int i = 1; i <limit-1; ++i) {
            temp = temp + (matA[node][i]*vectorX[i]);
            std::cout<<"vector X "<<vectorX[i]<<" temp sum "<<node<<": "<<temp<<std::endl;
    }
    temp = temp/4;
    //std::cout<<"temp "<<node<<": "<<temp<<std::endl;
    temp = lambda*temp+(1-lambda)*vectorXold[node];
    //std::cout<<"temp relax "<<node<<": "<<temp<<std::endl;
    return  temp;
}

template <typename T>
void liebmann<T>::setUpEdge(int size) {
    T sum = upEdge.getTempDif(size-1);
    for(int i=0;i<size;++i){
        if(i==0){

            vectorX[i]=upEdge.getUp()+leftEdge.getUp();
        }
        else if(i==size-1){
            vectorX[i]=upEdge.getLow()+rightEdge.getUp();
        }
        else{
            vectorX[i] = upEdge.getUp()-(i*sum);
        }
    }
}

template <typename T>
void liebmann<T>::setDownEdge(int size) {
    T sum = botEdge.getTempDif(size-1);
    int offset = (size-1)*size;
    std::cout<<"offset "<<offset<<std::endl;
    for(int i=0;i<size;++i){
        if(i==0){
            vectorX[offset]=botEdge.getUp()+leftEdge.getLow();
        }
        else if(i==size-1){
            vectorX[offset+i]=botEdge.getLow()+rightEdge.getLow();
        }
        else{
            vectorX[offset+i] = botEdge.getUp()-(i*sum);
        }
    }
}

template <typename T>
void liebmann<T>::setRLEdge(int sizeX,int sizeY) {
    T sumL = leftEdge.getTempDif(sizeY-1);
    T sumR = rightEdge.getTempDif(sizeY-1);
    T offset(0);
    for (int j = 1; j <sizeY-1; ++j) {
        offset = j*sizeX;
        vectorX[offset] = leftEdge.getUp() -(j*sumL);
        vectorX[offset + sizeX-1] = rightEdge.getUp() -(j*sumR);
        }
}

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

template <typename T>
void liebmann<T>::printX() {
    for (int j = 0; j <vectorX.size() ; ++j) {
        std::cout<<"Node "<<j<<": "<<vectorX[j]<<std::endl;
    }
}

template <typename T>
T liebmann<T>::error(int node) {
    T error =std::abs((vectorX[node]-vectorXold[node])/vectorX[node])*100;
    //std::cout<<"error node "<<node<<" "<<error<<std::endl;
    return error;
}