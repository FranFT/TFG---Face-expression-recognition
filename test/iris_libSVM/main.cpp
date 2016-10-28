#include <iostream>
#include "utilidades.h"
#include "svm.h"

using namespace std;

// Variables necesarias para SVM.
struct svm_problem prob;
struct svm_parameter param;
struct svm_model *modelo;

// Indica el número de entradas que contiene el fichero.
int contar_lineas(const char* _file_path){
	// Variables necesarias.
	int num_lineas = 0;
	string linea;
	ifstream fichero_entrada;
	
	// Cuerpo de la función.
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

// Lee el fichero que contiene el conjunto de datos.
bool leeFichero(const char* _file_path){
	// Variables necesarias.
	ifstream fichero_entrada;
	bool salida = true;
	
	(contar_lineas(_file_path) > 0) ? salida = true : salida = false;
	
	// Valor de retorno.
	return salida;
}

// Programa principal.
int main(int argc, char** argv){
	// Variables necesarias.
	const char* file_path = "../data/irisDataset/iris.data";
	
	if(leeFichero(file_path))
		cout << "Exito" << endl;

	return 0;
}
