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
    //printX();
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

        case 9:
            matA[nodeX][nodeX+maxY]=1;
            matA[nodeX][nodeX-maxY]=1;
            matA[nodeX][nodeX-1]=1;
            matA[nodeX][nodeX+1]=1;
            break;
    }

}

template <typename T>
void liebmann<T>::solveLiebmann(anpi::Matrix<T> matA) {
    int limit = matA.rows();
    int  cont(0);
    end=false;
    while (!end&&cont<500) {
        //#pragma omp parallel for
        for (int i = 0; i < limit; ++i) {
            if (cont > 0) {
                vectorXold[i] = vectorX[i]; }
            getNodeTem(matA, i, limit);
        }
        //printX();
        cont++;
    }
    std::cout<<"\nnumber count "<<cont<<"\n"<<std::endl;
    //printX();
}

template <typename T>
T liebmann<T>::getNodeTem(anpi::Matrix<T> matA, int node,int limit) {
    T temp(0);
    T es = std::sqrt(std::numeric_limits<T>::epsilon());
    for (int i = 0; i <limit; ++i) {
        if(i!=node) {
            temp = temp + (matA[node][i] * vectorX[i]);
            //std::cout<<"vector X "<<vectorX[i]<<" temp sum "<<node<<": "<<temp<<std::endl;
        }

    }
    if(temp==0){return vectorX[node];}
    temp = temp/4;
    //std::cout<<"temp "<<node<<": "<<temp<<std::endl;
    temp = lambda*temp+(1-lambda)*vectorXold[node];
    //std::cout<<"temp relax "<<node<<": "<<temp<<std::endl;
    vectorX[node]=temp;
    if(error(sqrt(limit)+1)<es){end=true;}
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
    return error;
}

template <typename T>
anpi::Matrix<T> liebmann<T>::generateFinalMat(anpi::Matrix<T> model) {
    int count(0);
    anpi::Matrix<T> res(model.rows(),model.cols(),T(0));
    for (int i = 0; i <model.rows() ; ++i) {
        for (int j = 0; j <model.cols() ; ++j) {
            res[i][j]=vectorX[count];
            ++count;
        }
    }
    return res;
}