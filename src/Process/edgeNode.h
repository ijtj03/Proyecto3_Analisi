/**
*  Clase PlotQuiver. Con esta clase se pueden los bordes de la placa metalica con un rango
*/
#ifndef ANPI_EDGENODE_H
#define ANPI_EDGENODE_H

template <typename T>
class edgeNode {
private:
   /** 
   * Variable privada.
   * Donde se guarda el valor del borde arriba.
   */    
    T upper;
   /** 
   * Variable privada.
   * Donde se guarda el valor del borde 
   */    
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
