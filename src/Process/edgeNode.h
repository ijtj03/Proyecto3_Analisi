//
// Created by av10 on 04/11/17.
//

#ifndef ANPI_EDGENODE_H
#define ANPI_EDGENODE_H

template <typename T>
class edgeNode {
private:
    T upper;
    T lower;
public:
    edgeNode(T,T);
    edgeNode();
    virtual ~edgeNode();
    T getTempDif(int);
    T getLow(){return lower;}
    T getUp(){return upper;}
};


#endif //ANPI_EDGENODE_H
