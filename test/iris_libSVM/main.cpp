#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "svm.h"

using namespace std;

// Tipo estructurado que representa cada entrada de 'irisDataset'.
struct Muestra{
	int clase;
	float atributos[4];
};

// Variables necesarias para SVM.
struct svm_problem prob;
struct svm_parameter param;
struct svm_model *modelo;

void mostrar(const vector<Muestra>& _vector){
	for(vector<Muestra>::const_iterator it = _vector.begin(); it!= _vector.end(); ++it){
		cout << "Atrr1: " << (*it).atributos[0] <<
		", Atrr2: " << (*it).atributos[1] <<
 		", Atrr3: " << (*it).atributos[2] <<
		", Atrr4: " << (*it).atributos[3] <<
		", clase: " << (*it).clase << endl;
	}
}

// Indica el número de entradas que contiene el fichero.
int contar_lineas(const char* _file_path){
	/***************************
	**	Variables necesarias	**
	***************************/
	int num_lineas = 0;
	string linea;
	ifstream fichero_entrada;
	
	/***************************
	**	Cuerpo de la función	**
	***************************/
	fichero_entrada.open(_file_path);
	
	// Si el fichero se abrió correctamente, cuento el número de lineas.
	if(fichero_entrada.is_open())	
		while(getline(fichero_entrada, linea))
			num_lineas++;
	
	// Cierro el fichero.	
	fichero_entrada.close();
		
	// Valor devuelto.	
	return num_lineas;
}

bool insertar_muestra(Muestra &_muestra, string _linea){
	/***************************
	**	Variables necesarias	**
	***************************/
	int attr = 0;
	bool salida = true;
	string aux = "";
	
	/***************************
	**	Cuerpo de la función	**
	***************************/
	for(int i = 0; i < _linea.size(); i++){
		if(_linea.at(i) == ','){
			_muestra.atributos[attr] = stof(aux);
			aux.clear();
			attr++;
		}
		else if(i+1 == _linea.size()){
			aux += _linea.at(i);
			if(aux == "Iris-setosa")
				_muestra.clase = 001;
			else if(aux == "Iris-versicolor")
				_muestra.clase = 010;
			else if(aux == "Iris-virginica")
				_muestra.clase = 100;
			else{
				_muestra.clase = -1;
				salida = false;
			}		
		}
		else{
			aux += _linea.at(i);
		}
	}
	
	return salida;
}

// Lee el fichero que contiene el conjunto de datos.
bool leeFichero(const char* _file_path, vector<Muestra>& _poblacion){
	/***************************
	**	Variables necesarias	**
	***************************/
	int nlineas = 0;
	bool salida = true;
	string linea;
	ifstream fichero_entrada;
	
	/***************************
	**	Cuerpo de la función	**
	***************************/
	// Cuento el número de líneas de fichero.
	nlineas = contar_lineas(_file_path);
	if(nlineas == 0)
		salida = false;
	else{
		// Reservo memoria para los datos del fichero.	
		_poblacion = vector<Muestra>(nlineas);
	
		// Abro el fichero	
		fichero_entrada.open(_file_path);
	
		// Inserto cada una de las muestras del fichero en el vector.
		for(int i=0; i<nlineas; i++){
			getline(fichero_entrada, linea);
			if(!insertar_muestra(_poblacion.at(i), linea))
				salida = false;
		}
			
		fichero_entrada.close();	
	}

	// Valor de retorno.
	return salida;
}

// Programa principal.
int main(int argc, char** argv){
	/***************************
	**	Variables necesarias	**
	***************************/
	const char* file_path = "../data/irisDataset/iris.data";
	vector<Muestra> poblacion;
	
	/***************************
	**	Cuerpo de la función	**
	***************************/
	if(leeFichero(file_path, poblacion)){
		mostrar(poblacion);
	}

	return 0;
}
