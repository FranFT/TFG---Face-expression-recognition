#include "OpenCVApps.h"

OpenCVApps::OpenCVApps(){
	//http://stackoverflow.com/questions/143174/how-do-i-get-the-directory-that-a-program-is-running-from
	// Obtenemos la ruta del directorio actual.
	char bufferAux[FILENAME_MAX];

	ruta_proyecto = String(_getcwd(bufferAux, sizeof(bufferAux)));
	create_samples = "createsamples.bat";
	train_cascade = "traincascade.bat";
	directorio_clasificador = "data\\clasificador";
	directorio_ficheros_info = "samples\\positive_samples\\";
	directorio_ficheros_background = "samples\\background_samples\\";
	directorio_ficheros_vec = "vec_files\\";
	formato_ficheros_info = ".info";
	formato_ficheros_vec = ".vec";
	formato_ficheros_background = ".txt";

	expresiones.push_back("centerlight");
	expresiones.push_back("glasses");
	expresiones.push_back("happy");
	expresiones.push_back("leftlight");
	expresiones.push_back("noglasses");
	expresiones.push_back("normal");
	expresiones.push_back("rightlight");
	expresiones.push_back("sad");
	expresiones.push_back("sleepy");
	expresiones.push_back("surprised");
	expresiones.push_back("wink");

	numero_muestras = "12";

	// Parámetros para el entrenamiento.
	numPos = "11";
	numNeg = "120";
	numStages = "2";
	featureType = "LBP";
}

void OpenCVApps::generar_ficheros_bat(){
	String base;
	String linea;
	ofstream fichero;

	// En primer lugar se crea el fichero createsamples.bat
	fichero.open(create_samples, ios::out | ios::trunc);
	fichero << "cd " + ruta_proyecto << endl;

	base = "CALL opencv_createsamples.exe -info " + directorio_ficheros_info;
	for (int i = 0; i < expresiones.size(); i++){
		linea = base + expresiones.at(i) + formato_ficheros_info +
			" -vec " + directorio_ficheros_vec + expresiones.at(i) + formato_ficheros_vec +
			" -num " + numero_muestras;

		fichero << linea << endl;
	}

	fichero.close();

	// En segundo lugar se crea el fichero traincascade.bat
	fichero.open(train_cascade, ios::out | ios::trunc);
	fichero << "cd " + ruta_proyecto << endl;

	base = "CALL opencv_traincascade.exe -data " + directorio_clasificador;
	for (int i = 0; i < expresiones.size(); i++){
		linea = base + "_" + expresiones.at(i) +
			" -vec " + directorio_ficheros_vec + expresiones.at(i) + formato_ficheros_vec +
			" -bg " + directorio_ficheros_background + expresiones.at(i) + formato_ficheros_background +
			" -numPos " + numPos +
			" -numNeg " + numNeg +
			" -numStages " + numStages +
			" -featureType " + featureType;

		fichero << linea << endl;
	}

	fichero.close();
}

