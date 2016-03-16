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

// Clase que se encarga de utilizar las aplicaciones de OpenCV "opencv_traincascade.exe" y "opencv_createsamples.exe".
// Para ello, crea dos archivos.bat (uno para "opencv_traincascade.exe" y otro para "opencv_createsamples.exe") que
// ejecutará en un terminal generando (mediante "opencv_createsamples.exe") los archivos.vec necesarios para entrenar
// el clasificador (mediante "opencv_traincascade.exe"). Nota: Ambos ejecutables deben estar en la carpeta del proyecto.
//
// Además contiene todos los parámetros empleados en el entrenamiento y cadenas necesarias para invocar estas aplicaciones.
class OpenCVApps{
private:
	vector<String> expresiones;
	String ruta_proyecto;
	String nombre_fichero1;
	String nombre_fichero2;
	String directorio_clasificador;
	String directorio_ficheros_info;
	String directorio_ficheros_background;
	String directorio_ficheros_vec;
	String formato_ficheros_info;
	String formato_ficheros_vec;
	String formato_ficheros_background;

	String numero_muestras;
	String sample_width;
	String sample_height;
	String numPos;
	String numNeg;
	String numStages;
	String featureType;

	void ejecutar_fichero_bat(static TCHAR* lpCommandLine);
public:
	OpenCVApps();
	~OpenCVApps(){};
	void generar_ficheros_bat();
	void create_samples();
	void train_cascade();
};

#endif