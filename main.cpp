#include "utilidades.h"
#include "expresion.h"
//#include <opencv2\objdetect\objdetect.hpp>


#define NUM_IMAGES 165


// Fase de entrenamiento.
vector<expresion> inicializar_expresiones(const float _size_training, bool _salida=false){
	vector<expresion> expresiones;
	expresion aux;
	for (int i = 0; i < NUM_EXPRESIONES; i++){
		if (aux.cargar_expresion(static_cast<tipo_expresion>(i), true, false))
			expresiones.push_back(aux);
		else if (_salida)
			cerr << "ERROR: No se ha podido cargar la expresion facial - " << static_cast<tipo_expresion>(i) << endl;
	}

	return expresiones;
}


int main(){
	const float size_training = 0.8;
	inicializar_expresiones(size_training);

	return 0;
}