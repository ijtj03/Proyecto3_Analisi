//
// Created by av10 on 04/11/17.
//

#include "edgeNode.h"

/**
* Constructor.
* Para instanciar la clase.
* @param pUp Valor mas alto del borde
* @param pLow Valor mas bajo del borde
*/
template <typename T>
edgeNode<T>::edgeNode(T pUp,T pLow) {
    // TODO Auto-generated constructor stub
    upper = pUp;
    lower = pLow;

}

/**
* Constructor.
* Para instanciar la clase.
*/
template <typename T>
edgeNode<T>::edgeNode() {
    // TODO Auto-generated constructor stub


}

/**
* Destructor.
* Para destruir instancias de la clase.
*/
template <typename T>
edgeNode<T>::~edgeNode() {
    // TODO Auto-generated destructor stub
}

/**
* Miembro normal que recibe dos argumento y retorna un dato de tipo T
* @param total int para saber cuantas filas  columnas tiene la matriz
* @return dato tipo T que sabe de cuanto en cuanto varia el borde.
*/
template<typename T>
T edgeNode<T>::getTempDif(int total) {
    T dif = (upper-lower)/total;
    return dif;
}
