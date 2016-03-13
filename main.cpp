#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include "utilidades.h"
#include "expresion.h"

/** Fase de preparaci�n de los datos.
*	Para cada uno de los tipos de expresi�n se crea un objeto del tipo 'expresion'. Para cada uno de estos objetos:
*		-Se leen las im�genes correspondientes a la expresi�n de la base de datos 'yalefaces'.
*		-Se asigna cada imagen leida a una muestra de training. El resto ser�n usadas como muestra de test.
*		-Se busca la cara existente en cada una de dichas im�genes, con el fin de definir una regi�n que ser� usada
*		en la creaci�n de los ficheros necesarios para el entrenamiento del clasificador.
*		-Por �ltimo se crean los ficheros necesarios para realizar el entrenamiento del clasificador:
*			-Ficheros con la ruta de las im�genes de casos positivos pertenecientes a la muestra de training de dicha expresi�n.
*			-Ficheros con la ruta de las im�genes de casos negativos pertenecientes a la muestra de training de dicha expresi�n.
*/
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

/**
*	Esta funci�n ejecuta el fichero .bat indicado como argumento. Se emplear� para ejecutar las aplicaciones 'opencv_createsamples.exe' y
*	'opencv_traincascade.exe'.

*	Esta funci�n crea cada uno de los ficheros .vec necesarios para usar el m�dulo 'opencv_traincascade.exe' que es el encargado de entrenar al
*	clasificador.
*	Para ello invoca un proceso que ejecuta un archivo .bat (script) que ejecuta la aplicaci�n 'opencv_createsamples.exe' incluida en OpenCV con
*	cada uno de las distintas expresiones faciales, generando de esta manera el correspondiente fichero .vec. Esta aplicaci�n hace uso del fichero
*	de casos positivos creado en la funci�n "inicializar_expresiones()".
*/
void ejecutar_fichero_bat(LPTSTR lpCommandLine){
	PROCESS_INFORMATION informacion_proceso;
	STARTUPINFO informacion_arranque;
	LPCTSTR lpApplicationName = "C:\\Windows\\System32\\cmd.exe";
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

int main(){
	const float size_training = 0.8;
	LPTSTR _opencv_createsamples = "/c createsamples.bat";
	LPTSTR _opencv_traincascade = "/c traincascade.bat";

	inicializar_expresiones(size_training);
	ejecutar_fichero_bat(_opencv_createsamples);
	
	return 0;
}