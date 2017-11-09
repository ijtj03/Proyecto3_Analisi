//
// Created by av10 on 09/11/17.
//

#ifndef ANPI_USERINTERFACE_H
#define ANPI_USERINTERFACE_H


class userInterface {
public:
    userInterface();
    void init();
private:
    void setUpMat(int,int);
    edgeNode<double> getEdge(std::string);
    void calcMat(anpi::Matrix<double>,liebmann<double>);
    void graphMat(anpi::Matrix<double>,liebmann<double>);
};


#endif //ANPI_USERINTERFACE_H
