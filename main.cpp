#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include "utilidades.h"
#include "expresion.h"
#include "OpenCVApps.h"
using namespace std;
/** Fase de preparación de los datos.
*	Para cada uno de los tipos de expresión se crea un objeto del tipo 'expresion'. Para cada uno de estos objetos:
*		-Se leen las imágenes correspondientes a la expresión de la base de datos 'yalefaces'.
*		-Se asigna cada imagen leida a una muestra de training. El resto serán usadas como muestra de test.
*		-Se busca la cara existente en cada una de dichas imágenes, con el fin de definir una región que será usada
*		en la creación de los ficheros necesarios para el entrenamiento del clasificador.
*		-Por último se crean los ficheros necesarios para realizar el entrenamiento del clasificador:
*			-Ficheros con la ruta de las imágenes de casos positivos pertenecientes a la muestra de training de dicha expresión.
*			-Ficheros con la ruta de las imágenes de casos negativos pertenecientes a la muestra de training de dicha expresión.
*/
vector<expresion> inicializar_expresiones(const float _size_training, bool _salida=false){
	vector<expresion> expresiones;
	expresion aux;
	for (int i = 0; i < NUM_EXPRESIONES; i++){
		if (aux.cargar_expresion(static_cast<tipo_expresion>(i), false, false))
			expresiones.push_back(aux);
		else if (_salida)
			cerr << "ERROR: No se ha podido cargar la expresion facial - " << static_cast<tipo_expresion>(i) << endl;
	}

	return expresiones;
}

int main(){
	const float size_training = 0.8;
	OpenCVApps aplicaciones_OpenCV;

	inicializar_expresiones(size_training);
	aplicaciones_OpenCV.generar_ficheros_bat();
	aplicaciones_OpenCV.create_samples();
	aplicaciones_OpenCV.train_cascade();
	pintaI(Mat::zeros(50, 50, CV_8S));
	return 0;
}