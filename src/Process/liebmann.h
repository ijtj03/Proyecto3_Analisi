//
// Created by av10 on 31/10/17.
//

#ifndef ANPI_LIEBMANN_H
#define ANPI_LIEBMANN_H


#include "edgeNode.h"

template <typename T>
class liebmann {
private:
    std::vector<T> vectorX;
    std::vector<T> vectorXold;
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
    void fillMat(anpi::Matrix<T>&,int,int,int);
    int identifyNode(int,int,int);
    bool isNeighbor(int);
    void printMyMat(anpi::Matrix<T>);
    void solveLiebmann(anpi::Matrix<T>);
    T getNodeTem(anpi::Matrix<T>,int,int);
    void setUpEdge(int);
    void setDownEdge(int);
    void setRLEdge(int,int);
    T error(int);
    void printX();
    anpi::Matrix<T> generateFinalMat(anpi::Matrix<T>);

};


#endif //ANPI_LIEBMANN_H
