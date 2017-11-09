//
// Created by av10 on 31/10/17.
//

#ifndef ANPI_LIEBMANN_H
#define ANPI_LIEBMANN_H


#include "edgeNode.h"

template <typename T>
class liebmann {
private:
    T lambda;
    bool end=false;
    edgeNode<T> upEdge;
    edgeNode<T> botEdge;
    edgeNode<T> leftEdge;
    edgeNode<T> rightEdge;
public:
    liebmann(T,edgeNode<T>,edgeNode<T>,edgeNode<T>,edgeNode<T>);
    virtual ~liebmann();
    anpi::Matrix<T> generateMat(anpi::Matrix<T>);
    void printMyMat(anpi::Matrix<T>);
    void solveLiebmannOMP(anpi::Matrix<T>&,T);
    void solveLiebmann(anpi::Matrix<T>);
    T getNodeTem(anpi::Matrix<T>&,int,int);
    void setUpEdge(int,anpi::Matrix<T>&);
    void setDownEdge(int,int,anpi::Matrix<T>&);
    void setRLEdge(int,int,anpi::Matrix<T>&);
    T error(T,T);
    T getMax(std::vector<T>);
    anpi::Matrix<T> generateFinalMat(anpi::Matrix<T>);

};


#endif //ANPI_LIEBMANN_H
