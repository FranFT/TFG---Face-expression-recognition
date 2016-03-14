#ifndef __OPENCVAPPS__
#define __OPENCVAPPS__

#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <direct.h>
#include <fstream>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

class OpenCVApps{
private:
	vector<String> expresiones;
	String ruta_proyecto;
	String create_samples;
	String train_cascade;
	String directorio_clasificador;
	String directorio_ficheros_info;
	String directorio_ficheros_background;
	String directorio_ficheros_vec;
	String formato_ficheros_info;
	String formato_ficheros_vec;
	String formato_ficheros_background;

	String numero_muestras;
	String numPos;
	String numNeg;
	String numStages;
	String featureType;

	void ejecutar_fichero_bat(LPTSTR lpCommandLine);
public:
	OpenCVApps();
	~OpenCVApps(){};
	void generar_ficheros_bat();
	void create_samples();
	void train_cascade();
};

#endif