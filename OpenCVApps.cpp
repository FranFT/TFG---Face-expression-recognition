#include "OpenCVApps.h"

OpenCVApps::OpenCVApps(){
	//http://stackoverflow.com/questions/143174/how-do-i-get-the-directory-that-a-program-is-running-from
	// Obtenemos la ruta del directorio actual.
	char bufferAux[FILENAME_MAX];

	ruta_proyecto = String(_getcwd(bufferAux, sizeof(bufferAux)));
	nombre_fichero1 = "createsamples.bat";
	nombre_fichero2 = "traincascade.bat";
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
	sample_width = "48";
	sample_height = "48";

	// Parámetros para el entrenamiento.
	numPos = "11";
	numNeg = "120";
	numStages = "5";
	featureType = "LBP";
}

void OpenCVApps::generar_ficheros_bat(){
	String base;
	String linea;
	ofstream fichero;

	// En primer lugar se crea el fichero createsamples.bat
	fichero.open(nombre_fichero1, ios::out | ios::trunc);
	fichero << "cd " + ruta_proyecto << endl;

	base = "CALL opencv_createsamples.exe -info " + directorio_ficheros_info;
	for (unsigned int i = 0; i < expresiones.size(); i++){
		linea = base + expresiones.at(i) + formato_ficheros_info +
			" -vec " + directorio_ficheros_vec + expresiones.at(i) + formato_ficheros_vec +
			" -num " + numero_muestras +
			" -w " + sample_width +
			" -h " + sample_height;

		fichero << linea << endl;
	}

	fichero.close();

	// En segundo lugar se crea el fichero traincascade.bat
	fichero.open(nombre_fichero2, ios::out | ios::trunc);
	fichero << "cd " + ruta_proyecto << endl;

	base = "CALL opencv_traincascade.exe -data " + directorio_clasificador;
	for (unsigned int i = 0; i < expresiones.size(); i++){
		linea = base + "_" + expresiones.at(i) +
			" -vec " + directorio_ficheros_vec + expresiones.at(i) + formato_ficheros_vec +
			" -bg " + directorio_ficheros_background + "bg_" + expresiones.at(i) + formato_ficheros_background +
			" -numPos " + numPos +
			" -numNeg " + numNeg +
			" -numStages " + numStages +
			" -w " + sample_width +
			" -h " + sample_height +
			" -featureType " + featureType;

		fichero << linea << endl;
	}

	fichero.close();
}

/**
*	Esta función ejecuta el fichero .bat indicado como argumento. Se empleará para ejecutar las aplicaciones 'opencv_createsamples.exe' y
*	'opencv_traincascade.exe'.
*/
void OpenCVApps::ejecutar_fichero_bat(static TCHAR* lpCommandLine){
	PROCESS_INFORMATION informacion_proceso;
	STARTUPINFO informacion_arranque;

	//LPCTSTR lpApplicationName = "C:\\Windows\\System32\\cmd.exe";
	static const TCHAR* lpApplicationName = TEXT("C:\\Windows\\System32\\cmd.exe");
	//LPTSTR lpCommandLine = "/c createsamples.bat";

	ZeroMemory(&informacion_arranque, sizeof(informacion_arranque));
	informacion_arranque.cb = sizeof(informacion_arranque);
	ZeroMemory(&informacion_proceso, sizeof(informacion_proceso));

	//https://msdn.microsoft.com/en-us/library/windows/desktop/ms682425(v=vs.85).aspx
	//https://msdn.microsoft.com/en-us/library/ms682512(VS.85).aspx
	// Iniciamos el proceso que crea los ficheros .vec
	if (!CreateProcess(lpApplicationName, lpCommandLine, NULL, NULL, TRUE, 0, NULL, NULL, &informacion_arranque, &informacion_proceso)){
		cerr << "ERROR: No se pudo iniciar el proceso - opencv_createsamples.exe" << endl;
	}
	// Esperamos hasta que el proceso creado finalice.
	WaitForSingleObject(informacion_proceso.hProcess, INFINITE);

	// Se cierra el proceso.
	CloseHandle(informacion_proceso.hProcess);
	CloseHandle(informacion_proceso.hThread);
}

void OpenCVApps::create_samples(){
	static TCHAR* lpCommandLine = TEXT("/c createsamples.bat");
	ejecutar_fichero_bat(lpCommandLine);
}

void OpenCVApps::train_cascade(){
	static TCHAR* lpCommandLine = TEXT("/c traincascade.bat");
	ejecutar_fichero_bat(lpCommandLine);

}


