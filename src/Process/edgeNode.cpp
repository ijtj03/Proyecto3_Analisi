//
// Created by av10 on 04/11/17.
//

#include "edgeNode.h"

template <typename T>
edgeNode<T>::edgeNode(T pUp,T pLow) {
    // TODO Auto-generated constructor stub
    upper = pUp;
    lower = pLow;

}

template <typename T>
edgeNode<T>::edgeNode() {
    // TODO Auto-generated constructor stub


}


template <typename T>
edgeNode<T>::~edgeNode() {
    // TODO Auto-generated destructor stub
}

template<typename T>
T edgeNode<T>::getTempDif(int total) {
    T dif = (upper-lower)/total;
    return dif;
}