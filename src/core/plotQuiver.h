/**

ANPI
Metodos para realizar graficas x,y usando Matplotlib (Python)
@Autor: David Badilla S.
@Description: Clase que se utiliza para poder realizar graficas de puntos x y
	      usando como base la biblioteca Matplotlib de Python. La comuni-
	      se establece mediante Python.h, lo cual permite ejecutar codigo 
	      de Python desde c++.
@Contact: davbs94@gmail.com


*/

#ifndef PLOTPY_H
#define PLOTPY_H

#include <python2.7/Python.h>
#include <stdlib.h>
#include <string>
#include <vector>


/**
El paquete plotpy contiene los metodos necesarios para realizar
graficas xy.
*/

namespace plotpy{



template<typename T>
class  PlotQuiver{

	private:
		//Titulo de la grafica.
		anpi::Matrix<T> _data;

	public:
		
		PlotQuiver();

		~PlotQuiver();

		void initialize(anpi::Matrix<T> data);

		void showPlots();

		std::string getData(anpi::Matrix<T> data,std::string varName);

		void plotColor();

		void plotQuiver();

		//std::string getData(anpi::Matrix<T> data,std::string varName);


}; 


template <typename T>
PlotQuiver<T>::PlotQuiver(){}


template <typename T>
PlotQuiver<T>::~PlotQuiver(){}


template <typename T>
void PlotQuiver<T>::initialize(anpi::Matrix<T> data){
    Py_Initialize();
    PyRun_SimpleString("import numpy as np");
    PyRun_SimpleString("import pylab as plt");
    std::string auxFun ="def getAuxMats(Z):					\n";
	auxFun.append("	dx = np.linspace(0,len(Z[0])-1,len(Z[0]))		\n");
	auxFun.append("	dy = np.linspace(0,len(Z)-1,len(Z))			\n");
	auxFun.append("	X,Y = np.meshgrid(dx,dy)				\n");
	auxFun.append("	zMax = np.amax(Z)					\n");
	auxFun.append("	u = np.zeros((len(Z),len(Z[0])))			\n");
	auxFun.append("	v = np.zeros((len(Z),len(Z[0])))			\n");
	auxFun.append("	a,b=0,0							\n");
	auxFun.append("	posMax=np.array([])					\n");
	auxFun.append("	for x in Z:						\n");
	auxFun.append("		for y in x:					\n");
	auxFun.append("			if (y==zMax):				\n");
	auxFun.append("				posMax = np.array([a,b])	\n");
	auxFun.append("				break				\n");
	auxFun.append("			b+=1					\n");
	auxFun.append("		a+=1						\n");
	auxFun.append("		b=0						\n");
	auxFun.append("	a,b=0,0							\n");
	auxFun.append("	for x in Z:						\n");
	auxFun.append("		for y in x:					\n");
	auxFun.append("			v[a][b]=posMax[0]-a			\n");
	auxFun.append("			u[a][b]=b-posMax[1]			\n");			
	auxFun.append("			b+=1					\n");
	auxFun.append("		a+=1						\n");
	auxFun.append("		b=0						\n");
	auxFun.append("	return [X,Y,u,v]					\n");
    PyRun_SimpleString(auxFun.c_str());
    _data = data;
    
    std::string tmp1 = getData(data,"z"); 
    PyRun_SimpleString(tmp1.c_str());
}



template <typename T>
std::string PlotQuiver<T>::getData(anpi::Matrix<T> mat,std::string varName){
    std::string tmp1 = varName + " = np.array([";
    for (int i = 0; i < mat.rows(); ++i)
	{
    		tmp1.append("[");
		for (int j = 0; j < mat.cols(); ++j){
			tmp1.append(std::to_string(mat[i][j])+",");
		}
	tmp1.append("],");
    }
    tmp1.append("])");
    return tmp1;
}
/*
*@brief Metodo que despliega todas las figuras que se han creado antes de hacer este llamado
*
*
*
*/
template <typename T>
void PlotQuiver<T>::showPlots(){
    PyRun_SimpleString("plt.show()");
}

template <typename T>
void PlotQuiver<T>::plotColor(){
    PyRun_SimpleString("plt.imshow(z)");
    PyRun_SimpleString("plt.colorbar()");
}
template <typename T>
void PlotQuiver<T>::plotQuiver(){
    PyRun_SimpleString("auxVar = getAuxMats(z)");
    PyRun_SimpleString("plt.quiver(auxVar[0],auxVar[1],auxVar[2],auxVar[3],width=.01,linewidth=0.1)");
}

}

#endif // PLOTPY_H
