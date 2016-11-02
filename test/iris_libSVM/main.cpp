#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
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

// Función que muestra el vector de muestras por pantalla.
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

// Modifica una Muestra dada con el contenido de un string '_linea'.
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
	// Para cada caracter de la linea.
	for(int i = 0; i < _linea.size(); i++){
		// Se inserta el atributo correspondiente.
		if(_linea.at(i) == ','){
			_muestra.atributos[attr] = stof(aux);
			aux.clear();
			attr++;
		}
		// Se inserta la clase.
		else if(i+1 == _linea.size()){
			aux += _linea.at(i);
			if(aux == "Iris-setosa")
				_muestra.clase = 0;
			else if(aux == "Iris-versicolor")
				_muestra.clase = 1;
			else if(aux == "Iris-virginica")
				_muestra.clase = 2;
			else{
				_muestra.clase = -1;
				salida = false;
			}		
		}
		// Se acumula en 'aux' el elemento a insertar.
		else{
			aux += _linea.at(i);
		}
	}
	
	// Valor de retorno.
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

// Función que asigna cada muestra de la población a training o test.
bool calcular_muestra_training(
	vector<bool>& _perteneceTraining,
	const int _size,
	const float _sizeTraining = 0.8){
	/***************************
	**	Variables necesarias	**
	***************************/
	bool salida = true;
	int semilla;
	int indMax;
	vector<int> _training;
	

	/***************************
	**	Cuerpo de la función	**
	***************************/
	// Control de los parámetros de entrada.
	if(_size <= 0)
		salida = false;
	
	// Si el paŕametro es correcto.
	if(salida){	
		// Relleno el vector con los índices.
		for(int i=0; i<_size; i++)
			_training.push_back(i);
		
		// Inicializo el generador de números aleatorios.
		semilla = time(NULL);
		srand(semilla);
		
		// Barajo el vector.
		random_shuffle(_training.begin(), _training.end());

		// Asigno cada muestra a training en función del resultado de la instrucción anterior.
		if(!_perteneceTraining.empty())
			_perteneceTraining.clear();
		_perteneceTraining = vector<bool>(_size, false);
		
		// Número máximo de elementos que estarán en la muestra.
		indMax = ceil(_size * _sizeTraining);
		
		for(int i = 0; i < indMax; i++)
			_perteneceTraining.at( _training.at(i) ) = true;		
	}	
	
	
	return salida;
}

// Asigna los datos al dato estructurado 'svm_problem'.
void crear_problema(const vector<Muestra>& _poblacion, const vector<bool> _perteneceTraining){
	/***************************
	**	Variables necesarias	**
	***************************/
	int elementosTraining = 0;
	
	
	/***************************
	**	Cuerpo de la función	**
	***************************/
	// Cuantifico el número de elementos que hay en la muestra de training.
	for(vector<bool>::const_iterator it = _perteneceTraining.begin(); it != _perteneceTraining.end(); ++it)
		if((*it))
			elementosTraining++;
			
			
	prob.l = elementosTraining;
	prob.y = new double[]

}



// Programa principal.
int main(int argc, char** argv){
	/***************************
	**	Variables necesarias	**
	***************************/
	const char* file_path = "../data/irisDataset/iris.data";
	vector<Muestra> poblacion;
	vector<bool> perteneceTraining;
	
	/***************************
	**	Cuerpo de la función	**
	***************************/
	// Inserto las muestras del fichero en el vector.
	if(!leeFichero(file_path, poblacion))
		return 1;
	
	// Asigno cada muestra a training o test.
	if(!calcular_muestra_training(perteneceTraining, poblacion.size()))
		return 1;

	crear_problema(poblacion, perteneceTraining);

		

	return 0;
}
